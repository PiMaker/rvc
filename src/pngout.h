#ifndef PNGOUT_H
#define PNGOUT_H

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "mem.h"
#include "../tinypngout/TinyPngOut.h"

int write_ram_as_png(const char *p) {
    printf("Dumping RAM as '%s'...\n", p);

    const int WIDTH  = 2048;
	const int HEIGHT = 2048 - 128;
	uint8_t *pixels = malloc(3*WIDTH*HEIGHT);

    int px_idx = 0;
    for (int i = 0; i < MEM_SIZE; i += 4) {
        if (((i + 4) % 16) == 0) continue; // ignore alpha
        uint32_t m = (uint32_t)cpu.mem[i] |
            ((uint32_t)cpu.mem[i + 1] << 8) |
            ((uint32_t)cpu.mem[i + 2] << 16) |
            ((uint32_t)cpu.mem[i + 3] << 24);
        uint8_t val = (uint8_t)(((uint64_t)m * 255llu) / 0xffffffffllu);
        /* printf(" %d", val); */
        pixels[px_idx++] = val;
    }
	
	// Open output file
	FILE *fout = fopen(p, "wb");
	if (fout == NULL) {
		perror("Error: fopen");
        free(pixels);
		return EXIT_FAILURE;
	}
	
	// Initialize Tiny PNG Output
	struct TinyPngOut pngout;
	enum TinyPngOut_Status status = TinyPngOut_init(&pngout, (uint32_t)WIDTH, (uint32_t)HEIGHT, fout);
	if (status != TINYPNGOUT_OK) {
        perror("TinyPngOut create error");
        fclose(fout);
        free(pixels);
		return status;
    }
	
	// Write image data
	status = TinyPngOut_write(&pngout, pixels, (size_t)(WIDTH * HEIGHT));
	if (status != TINYPNGOUT_OK) {
        perror("TinyPngOut write error");
        fclose(fout);
        free(pixels);
        return status;
    }
	
	// Close output file
	if (fclose(fout) != 0) {
		perror("Error: fclose");
        free(pixels);
		return EXIT_FAILURE;
	}

    free(pixels);
	return EXIT_SUCCESS;
}

#endif
