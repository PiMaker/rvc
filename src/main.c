#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include "types.h"
#include "cpu.h"

#include "../elfy/elfy.h"

const int MEM_SIZE = 1024 * 1024 * 128;

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
    printf("Usage: rvc (-e <ELF binary>|-b <raw binary>) [-d <device tree binary>] [-v (0|1|2|3)] [-s]\n");
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) {
    char *elf = NULL;
    char *bin = NULL;
    char *dtb = NULL;

    int c;

    while ((c = getopt (argc, argv, "e:b:d:v:s")) != -1) {
        switch (c)
        {
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
            case '?':
            default:
                usage();
        }
    }

    if ((!elf && !bin) || (elf && bin)) {
        usage();
    }

    uint8_t *mem = malloc(MEM_SIZE);
    if (elf) {
        if (load_elf(elf, strlen(elf) + 1, mem, MEM_SIZE, VERBOSE >= 1)) {
            exit(EXIT_FAILURE+1);
        }
    } else if (bin) {
        uint8_t *bin_ptr = get_mmap_ptr(bin);
        memcpy(mem, bin_ptr, get_filesize(bin));
    }

    uint8_t *dtb_ptr = get_mmap_ptr("./dts.dtb");

    cpu_t cpu = cpu_init(mem, dtb_ptr);

    if (VERBOSE >= 1)
        printf("CPU initialized!\n");

    if (VERBOSE >= 3)
        cpu_dump(&cpu);

    while (1) {
        cpu_tick(&cpu);

        if (VERBOSE >= 3)
            cpu_dump(&cpu);

        if (SINGLE_STEP) {
            fflush(stdout);
            fflush(stdin);
            char ch;
            gc: ch = getchar();
            switch (ch) {
                case '\n': break;
                case 'c': SINGLE_STEP = 0; break;
                default: goto gc;
            }
        }
    }

    return 0;
}
