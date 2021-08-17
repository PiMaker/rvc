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

static bool got_ssip = false;
volatile static long long a = 0xaaaaffffffff;

// runs in supervisor mode via mideleg (machine-mode trap delegation)
void handle_trap(void) {
    print("[bare/trap] got SSIP!\n");
    got_ssip = true;
}

// called from assembly, runs in supervisor mode (via sret)
int main(void) {
    print("[bare] in main()\n");

    print("[bare] testing arithmetic...\n");

    long long b = a * 400LLU * -1;
    if (b != -0x10AAB2FFFFFFE70LL) {
        print("[bare] got wrong result :(\n");
    } else {
        print("[bare] got correct result!\n");
    }

    print("[bare] testing trap handler...\n");
    __asm volatile("csrw sip, 0x2");

    while (!got_ssip) {}

    print("[bare] selftest done!\n");
    print("[bare] now go run something more exciting...\n");

    while (true) {}

    return 0;
}
