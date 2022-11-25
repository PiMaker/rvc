#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
#include <sys/time.h>
#include "types.h"
#include "cpu.h"
#include "uart.h"
#include "net.h"
#include <termios.h>

#include "../elfy/elfy.h"
#include "pngout.h"

struct termios t, t_orig;
void buf_off(void)
{
    tcgetattr(STDIN_FILENO, &t);
    t_orig = t;
    t.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &t);
}

void buf_on(void)
{
    tcsetattr(STDIN_FILENO, TCSANOW, &t_orig);
}

static uint tracebuf[64];
static uint tracebuf_idx = 0;

void print_tracebuf() {
    if (cmd_buf == NULL) {
        cmd_buf = malloc(4096);
    }
    for (uint i = tracebuf_idx + 1; i != tracebuf_idx; i = (i + 1) % (sizeof(tracebuf) / sizeof(uint))) {
        printf("BACKTRACE: 0x %08x\n", tracebuf[i]);
        fflush(stdout);
        /* sprintf(cmd_buf, "addr2line -e linux/vmlinux %x", tracebuf[i]); */
        /* system(cmd_buf); */
    }
}

size_t get_filesize(const char* filename) {
    struct stat st;
    stat(filename, &st);
    return st.st_size;
}

uint8_t* get_mmap_ptr(const char* filename) {
    size_t filesize = get_filesize(filename);
    int fd = open(filename, O_RDONLY, 0);
    uint8_t* mmapped_data = mmap(NULL, filesize, PROT_READ, MAP_PRIVATE, fd, 0);
    return mmapped_data;
}

void usage() {
    printf("Usage: rvc (-e <ELF binary>|-b <raw binary>) [-d <device tree binary>] [-i <initramfs>] [-v (0|1|2|3|4)] [-s (single step)] [-t (trace)] [-x (allow exit ecall)] [-f (signal forward)] [-n <server socket path> / -N <client socket path>]\n");
    exit(EXIT_FAILURE);
}

static bool signal_forward = false;
#define MAX_INPUT_STACK 128
static char input_stack[MAX_INPUT_STACK];
static uint input_stack_idx = 0;
static time_t last_signal_time = 0;

void term(int signum)
{
    if (signal_forward) {
        time_t cur_time = time(NULL);
        if (cur_time - last_signal_time >= 1) {
            last_signal_time = cur_time;
            if (input_stack_idx > (MAX_INPUT_STACK - 2)) return;
            /* input_stack[input_stack_idx++] = 0x1b; */
            input_stack[input_stack_idx++] = 0x03; /* ETX / Ctrl-C */
            return;
        }
    }

    printf("\n\nCaught signal!\n");
    buf_on();
    cpu_dump(&cpu);
    printf("\n");

    /* ins_ret ret; */
    /* for (uint i = 0x10000; i < 0x11000; i += 4) { */
    /*     uint pa = mmu_translate(&ret, i, MMU_ACCESS_READ); */
    /*     uint val = mem_get_word(&cpu, pa); */
    /*     printf("%05x: %08x\n", i, val); */
    /* } */

    /* print_tracebuf(); */

    /* write_ram_as_png("ram.png"); */

    /* printf("\n"); */
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) {
    char *elf = NULL;
    char *bin = NULL;
    char *dtb = NULL;
    char *initrd = NULL;
    uint mtd_size = 0;

    char *socket = NULL;
    bool server = false;

    int c;
    bool trace = false;

    while ((c = getopt (argc, argv, "e:b:d:v:i:n:N:stxf")) != -1) {
        switch (c)
        {
            case 'f':
                signal_forward = true;
                break;
            case 'x':
                allow_ecall_exit = true;
                break;
            case 'e':
                elf = optarg;
                break;
            case 'b':
                bin = optarg;
                break;
            case 'd':
                dtb = optarg;
                break;
            case 'v':
                VERBOSE = atoi(optarg);
                break;
            case 's':
                SINGLE_STEP = 1;
                break;
            case 't':
                trace = true;
                break;
            case 'i':
                initrd = optarg;
                break;
            case 'n':
                socket = optarg;
                server = true;
                break;
            case 'N':
                socket = optarg;
                server = false;
                break;
            case '?':
            default:
                usage();
        }
    }

    if ((!elf && !bin) || (elf && bin)) {
        usage();
    }

    uint8_t *mem = malloc(MEM_SIZE);
    memset(mem, 0, MEM_SIZE);
    if (elf) {
        if (load_elf(elf, strlen(elf) + 1, mem, MEM_SIZE, VERBOSE >= 1)) {
            exit(EXIT_FAILURE+1);
        }
    } else if (bin) {
        uint8_t *bin_ptr = get_mmap_ptr(bin);
        memcpy(mem, bin_ptr, get_filesize(bin));
    }

    uint8_t *mtd = NULL;
    if (initrd) {
        mtd = malloc(MEM_SIZE);
        uint8_t *mtd_ptr = get_mmap_ptr(initrd);
        mtd_size = get_filesize(initrd);
        memcpy(mtd, mtd_ptr, mtd_size);
    }

    if (socket) {
        net_init(socket, server);
    }

    struct sigaction action;
    memset(&action, 0, sizeof(action));
    action.sa_handler = term;
    sigaction(SIGTERM, &action, NULL);
    sigaction(SIGINT, &action, NULL);

    fcntl(0, F_SETFL, O_NONBLOCK);

    cpu = cpu_init(mem, dtb ? get_mmap_ptr(dtb) : NULL, mtd, mtd_size);

    if (VERBOSE >= 1)
        printf("CPU initialized!\n");

    if (VERBOSE >= 3)
        cpu_dump(&cpu);

    setvbuf(stdin, NULL, _IONBF, 0);
    buf_off();

    // LIMITER (set to high number to ignore)
    const unsigned long restr = 200000*10000;
    unsigned long cur = 0;
    unsigned long t = time(NULL);

    uint init_verbose = VERBOSE;

    struct timeval now;
    gettimeofday(&now, NULL);
    uint64_t base_clock = now.tv_sec;

    while (1) {
        cur++;
        unsigned long t2 = time(NULL);
        if (t != t2) {
            cur = 0;
            t = t2;
        }
        if (cur >= restr) {
            continue;
        }

        gettimeofday(&now, NULL);
        _Time = (float)((now.tv_sec - base_clock) * 1000000 + now.tv_usec) / 1000000.0f;
        /* printf("Time: %lu %lu %.2f\n", now.tv_sec, now.tv_usec, _Time); */

        cpu_tick(&cpu);

        if (trace)
            printf("TRACE: PC=0x%08x\n", cpu.pc);

        tracebuf[tracebuf_idx++] = cpu.pc;
        if (tracebuf_idx >= (sizeof(tracebuf) / sizeof(uint))) {
            tracebuf_idx = 0;
        }

        /* if (cpu.clock > 1000000) { */
        /*     term(1); */
        /* } */

        /* if (cpu.clock > 5000000 && cpu.clock % 100000 == 0) { */
        /*     uint arb[8]; */
        /*     for (int iarb = 0; iarb < 8; iarb++) { */
        /*         uint arb_t = cpu.xreg[iarb*4+0] ^ */
        /*                     cpu.xreg[iarb*4+1] ^ */
        /*                     cpu.xreg[iarb*4+2] ^ */
        /*                     cpu.xreg[iarb*4+3]; */
        /*         arb[iarb] = arb_t; */
        /*     } */
        /*     uint arb_f = arb[0] ^ arb[1] ^ arb[2] ^ arb[3] ^ arb[4] ^ arb[5] ^ arb[6] ^ arb[7] ^ cpu.pc; */
        /*     printf("else if (cpu.clock == %d && arb != 0x%08x) ARB_FAIL\n", cpu.clock, arb_f); */
        /* } */

        /* if (cpu.pc == 0x80000118) { */
        /* if (cpu.clock == 6350505) { // divergence: 6350908 */
        /* if (cpu.clock == 6400000) { */
            /* printf("BREAKPOINT HIT\n"); */
            /* SINGLE_STEP = 1; */
            /* VERBOSE = 4; */
        /* } */

        if (VERBOSE >= 4)
            cpu_dump(&cpu);

        char input = 0;
        if (!SINGLE_STEP && input_stack_idx < MAX_INPUT_STACK && read(0, &input, 1)) {
            /* if (input == '+') { */
            /*     VERBOSE = (VERBOSE + 1) % 5; */
            /*     printf("\nVERBOSE = %d\n", VERBOSE); */
            /* } else { */
            /*     uart_input_value = input; */
            /* } */
            if (input)
                input_stack[input_stack_idx++] = input;
        }

        if (!uart_input_value && input_stack_idx > 0) {
            uart_input_value = input_stack[0];
            input_stack_idx--;
            // shift stack forward
            for (int i = 0; i < input_stack_idx; i++) {
                input_stack[i] = input_stack[i+1];
            }
        }

        if (SINGLE_STEP) {
            fflush(stdout);
            fflush(stdin);
            char ch;
            gc: ch = getchar();
            switch (ch) {
                case '\n': break;
                case 'c': SINGLE_STEP = false; VERBOSE = init_verbose; break;
                default: goto gc;
            }
        }
    }

    return 0;
}
