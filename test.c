#include <stdio.h>

#define OFFSET_UINT2_POS(x, y, w, h, n) uint2((x + n) % w, y + ((n + x) / h))
#define RAM_L1_ARRAY_IDX(a) (((a >> 2) & 127) | (((a >> 11) & 0x3) << 7))

void uint2(int x, int y) {
    printf("x=%d y=%d\n", x, y);
}

int main() {
    OFFSET_UINT2_POS(20, 0, 128, 128, 10);
    OFFSET_UINT2_POS(120, 0, 128, 128, 10);
    OFFSET_UINT2_POS(20, 3, 128, 128, 140);
    OFFSET_UINT2_POS(120, 0, 128, 128, (128*8 + 4));

    printf("\n");

    for (unsigned int i = 0; i < 128*128*16; i+=4) {
        printf("%03d: %d\n", i/4, RAM_L1_ARRAY_IDX(i));
    }

    return 0;
}
