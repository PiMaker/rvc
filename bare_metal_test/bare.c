#include <stdbool.h>

#define UART_THR (*(volatile unsigned char*)0x10000000)
#define UART_LSR (*(volatile unsigned char*)0x10000005)
#define UART_LSR_THRE 0x20

// wait for Transfer Hold Register to clear, then write character to print it
void uart_putc(unsigned char c) {
    while (UART_THR || !(UART_LSR & UART_LSR_THRE)) {}
    UART_THR = c;
}

void print(const char* str) {
    while (*str) {
        uart_putc(*str++);
    }
}

void print_hex(unsigned int number) {
    for (int i = 0; i < 8; i++) {
        switch (number & 0xF0000000) {
            case 0x00000000: uart_putc('0'); break;
            case 0x10000000: uart_putc('1'); break;
            case 0x20000000: uart_putc('2'); break;
            case 0x30000000: uart_putc('3'); break;
            case 0x40000000: uart_putc('4'); break;
            case 0x50000000: uart_putc('5'); break;
            case 0x60000000: uart_putc('6'); break;
            case 0x70000000: uart_putc('7'); break;
            case 0x80000000: uart_putc('8'); break;
            case 0x90000000: uart_putc('9'); break;
            case 0xA0000000: uart_putc('A'); break;
            case 0xB0000000: uart_putc('B'); break;
            case 0xC0000000: uart_putc('C'); break;
            case 0xD0000000: uart_putc('D'); break;
            case 0xE0000000: uart_putc('E'); break;
            case 0xF0000000: uart_putc('F'); break;
        }
        number <<= 4;
    }
}

static bool got_ssip = false;
volatile static long long a = 0xaaaaffffffff;

static int pattern_good = 0x12345678;
static int pattern_bad = 0xdeadbeef;

static char print_buf[256];

// runs in supervisor mode via mideleg (machine-mode trap delegation)
void handle_trap(void) {
    print("[bare/trap] got SSIP!\n");
    got_ssip = true;
}

// byte-for-byte memcpy
void memcpy_manual(unsigned char *dst, const unsigned char* src, int n) {
    for (int i = 0; i < n; i++) {
        dst[i] = src[i];
    }
}

// CSR-based memcpy
void memcpy_csr(unsigned char *dst, const unsigned char* src, int n) {
    print("[bare/memcpy_csr] src=0x");
    print_hex((unsigned int)src);
    print(" dst=0x");
    print_hex((unsigned int)dst);
    print("\n");
    __asm volatile ("csrw 0x0b1, %0" :: "r" (src));
    __asm volatile ("csrw 0x0b2, %0" :: "r" (dst));
    __asm volatile ("csrw 0x0b3, %0" :: "r" (n));
    __asm volatile ("csrw 0x0b0, %0" :: "r" (1) : "memory");
}

// called from assembly, runs in supervisor mode (via sret)
int main(void) {
    print("[bare] in main()\n");

    print("[bare] testing printing...\n[bare] 0x");
    print_hex(0xabcd1234);
    uart_putc('\n');

    print("[bare] testing arithmetic...\n");

    long long b = a * 400LLU * -1;
    if (b != -0x10AAB2FFFFFFE70LL) {
        print("[bare/error] got wrong result :(\n[bare/error] low=0x");
        print_hex((unsigned int)b);
        print("\n[bare/error] high=0x");
        print_hex((unsigned int)(b >> 32));
        print("\n");
        __asm volatile ("ebreak");
        while (true) {}
    } else {
        print("[bare] got correct result!\n[bare] low=0x");
        print_hex((unsigned int)b);
        print("\n[bare] high=0x");
        print_hex((unsigned int)(b >> 32));
        print("\n");
    }

    print("[bare] testing trap handler...\n");
    __asm volatile("csrw sip, 0x2");

    while (!got_ssip) {}

    print("[bare] testing memcpy...\n");
    int src[128];
    int dst_man[128];
    int dst_csr[128];

    for (int i = 0; i < 128; i++) {
        src[i] = pattern_good;
        dst_man[i] = pattern_bad;
        dst_csr[i] = pattern_bad;
    }

    memcpy_manual((unsigned char*)dst_man,
                  (const unsigned char*)src,
                  sizeof(src));

    memcpy_csr((unsigned char*)dst_csr,
               (const unsigned char*)src,
               sizeof(src));

    for (int i = 0; i < 128; i++) {
        int bad = ~0;

        if (dst_man[i] != src[i] || dst_man[i] != pattern_good) {
            print("[bare/error] memcpy (manual) failed\n");
            bad = dst_man[i];
        }
        if (dst_csr[i] != src[i] || dst_csr[i] != pattern_good) {
            print("[bare/error] memcpy (CSR) failed\n");
            bad = dst_csr[i];
        }

        if (bad != (~0)) {
            print("[bare/error] dst[0x");
            print_hex(i);
            print("] = 0x");
            print_hex(bad);
            print(" src[0x");
            print_hex(i);
            print("] = 0x");
            print_hex(src[i]);
            print("\n");
            __asm volatile ("ebreak");
            while (true) {}
        }
    }

    print("[bare] selftest done!\n");
    print("[bare] now go run something more exciting...\n");

    while (true) {}

    return 0;
}
