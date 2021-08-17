#ifndef UART_H
#define UART_H

<?:include header.p ?>

#define SHIFT_RBR 0
#define SHIFT_THR 8
#define SHIFT_IER 16
#define SHIFT_IIR 24
#define SHIFT_LCR 0
#define SHIFT_MCR 8
#define SHIFT_LSR 16
#define SHIFT_SCR 24

#define UART_GET1(x) ((cpu.uart.rbr_thr_ier_iir >> SHIFT_##x) & 0xff)
#define UART_GET2(x) ((cpu.uart.lcr_mcr_lsr_scr >> SHIFT_##x) & 0xff)

#define UART_SET1(x, val) cpu.uart.rbr_thr_ier_iir = (cpu.uart.rbr_thr_ier_iir & (~(0xff << SHIFT_##x))) | (val << SHIFT_##x)
#define UART_SET2(x, val) cpu.uart.lcr_mcr_lsr_scr = (cpu.uart.lcr_mcr_lsr_scr & (~(0xff << SHIFT_##x))) | (val << SHIFT_##x)

#define IER_RXINT_BIT 0x1
#define IER_THREINT_BIT 0x2

#define IIR_THR_EMPTY 0x2
#define IIR_RD_AVAILABLE 0x4
#define IIR_NO_INTERRUPT 0x7

#define LSR_DATA_AVAILABLE 0x1
#define LSR_THR_EMPTY 0x20

void uart_update_iir() {
    bool rx_ip = (UART_GET1(IER) & IER_RXINT_BIT) != 0 && UART_GET1(RBR) != 0;
    bool thre_ip = (UART_GET1(IER) & IER_THREINT_BIT) != 0 && UART_GET1(THR) == 0;
    UART_SET1(IIR, (rx_ip ? IIR_RD_AVAILABLE : (thre_ip ? IIR_THR_EMPTY : IIR_NO_INTERRUPT)));
}

void put_char_to_udon(uint c) {
    cpu.uart_buffer.ptr++;
    if (cpu.uart_buffer.ptr == <?= $uart_buffer_max + 1 ?>) {
        cpu.uart_buffer.ptr = 0;
    }
    [branch]
    switch (cpu.uart_buffer.ptr) {
<? for my $i (0..$uart_buffer_max) { print "case $i: cpu.uart_buffer.buf$i = c; break;\n"; } ?>
    }

    // check for overflow on Udon side, stall if necessary
    if (cpu.uart_buffer.ptr == _UdonUARTPtr - 1 ||
        (cpu.uart_buffer.ptr == <?= $uart_buffer_max ?> && _UdonUARTPtr == 0))
    {
        cpu.stall = STALL_UART;
    }
}

void uart_tick() {
    bool rx_ip = false;

    if ((cpu.clock % 128) == 0) {
        if (cpu.uart.input_tag != _UdonUARTInTag && UART_GET1(RBR) == 0) {
            cpu.uart.input_tag = _UdonUARTInTag;
            if (_UdonUARTInChar != 0) {
                UART_SET1(RBR, _UdonUARTInChar);
                cpu.debug_arb_0 = _UdonUARTInChar;
                UART_SET2(LSR, (UART_GET2(LSR) | LSR_DATA_AVAILABLE));
                uart_update_iir();
                if ((UART_GET1(IER) & IER_RXINT_BIT) != 0) {
                    rx_ip = true;
                }
            }
        }
    }

    uint thr = UART_GET1(THR);
    if ((cpu.clock % 16) == 0 && thr != 0) {
        put_char_to_udon(thr);
        UART_SET1(THR, 0);
        UART_SET2(LSR, (UART_GET2(LSR) | LSR_THR_EMPTY));
        uart_update_iir();
        if ((UART_GET1(IER) & IER_THREINT_BIT) != 0) {
            cpu.uart.thre_ip = true;
        }
    }

    if (!cpu.uart.interrupting && (cpu.uart.thre_ip || rx_ip)) {
        cpu.uart.interrupting = true;
        cpu.uart.thre_ip = false;
    } else {
        cpu.uart.interrupting = false;
    }
}

#endif
