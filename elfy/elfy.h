#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

int32_t load_elf(const char *path,
                 uint64_t path_len,
                 uint8_t *data,
                 uint64_t data_len,
                 bool verbose);
