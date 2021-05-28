/* #define VERBOSE */

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

// lots of inspiration from:
// https://github.com/takahirox/riscv-rust/blob/master/src/cpu.rs

#define handle_error(msg) \
    do { perror(msg); exit(EXIT_FAILURE); } while (0)

const int MEM_SIZE = 1024 * 1024 * 128;

int main(int argc, char *argv[]) {
    if (argc > 2 || (argc == 2 && !strcmp(argv[1], "--help"))) {
        printf("Usage: rvc [<ELF binary>]\n");
        exit(EXIT_FAILURE);
    }

    uint8_t *mem = malloc(MEM_SIZE);

    if (argc == 2) {
        load_elf(argv[1], strlen(argv[1]) + 1, mem, MEM_SIZE);
    }

    cpu_t cpu = cpu_init(mem);

    printf("CPU initialized!\n");

#ifdef VERBOSE
    cpu_dump(&cpu);
#endif

    while (1) {
        cpu_tick(&cpu);
#ifdef VERBOSE
        cpu_dump(&cpu);
#endif
    }

    return 0;
}
