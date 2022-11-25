#ifndef UART_H
#define UART_H



#define RAM_ADDR(lin) uint2(lin % 2048, 64 + (lin / 2048))
#define RAM_MAX (2048 * (4096 - 64) * 4 * 4)


/* shift by two to ignore byte offset */
#define RAM_L1_ARRAY_IDX(a) (((a >> 2) & 127) | (((a >> 11) & 0x3) << 7))


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

void put_byte_to_fb(uint c) {
    cpu.uart_buffer.ptr++;
    if (cpu.uart_buffer.ptr == 63) {
        cpu.stall = STALL_UART;
    }
    [forcecase]
    switch (cpu.uart_buffer.ptr) {
case 0: cpu.uart_buffer.buf0 = c; break;
case 1: cpu.uart_buffer.buf1 = c; break;
case 2: cpu.uart_buffer.buf2 = c; break;
case 3: cpu.uart_buffer.buf3 = c; break;
case 4: cpu.uart_buffer.buf4 = c; break;
case 5: cpu.uart_buffer.buf5 = c; break;
case 6: cpu.uart_buffer.buf6 = c; break;
case 7: cpu.uart_buffer.buf7 = c; break;
case 8: cpu.uart_buffer.buf8 = c; break;
case 9: cpu.uart_buffer.buf9 = c; break;
case 10: cpu.uart_buffer.buf10 = c; break;
case 11: cpu.uart_buffer.buf11 = c; break;
case 12: cpu.uart_buffer.buf12 = c; break;
case 13: cpu.uart_buffer.buf13 = c; break;
case 14: cpu.uart_buffer.buf14 = c; break;
case 15: cpu.uart_buffer.buf15 = c; break;
case 16: cpu.uart_buffer.buf16 = c; break;
case 17: cpu.uart_buffer.buf17 = c; break;
case 18: cpu.uart_buffer.buf18 = c; break;
case 19: cpu.uart_buffer.buf19 = c; break;
case 20: cpu.uart_buffer.buf20 = c; break;
case 21: cpu.uart_buffer.buf21 = c; break;
case 22: cpu.uart_buffer.buf22 = c; break;
case 23: cpu.uart_buffer.buf23 = c; break;
case 24: cpu.uart_buffer.buf24 = c; break;
case 25: cpu.uart_buffer.buf25 = c; break;
case 26: cpu.uart_buffer.buf26 = c; break;
case 27: cpu.uart_buffer.buf27 = c; break;
case 28: cpu.uart_buffer.buf28 = c; break;
case 29: cpu.uart_buffer.buf29 = c; break;
case 30: cpu.uart_buffer.buf30 = c; break;
case 31: cpu.uart_buffer.buf31 = c; break;
case 32: cpu.uart_buffer.buf32 = c; break;
case 33: cpu.uart_buffer.buf33 = c; break;
case 34: cpu.uart_buffer.buf34 = c; break;
case 35: cpu.uart_buffer.buf35 = c; break;
case 36: cpu.uart_buffer.buf36 = c; break;
case 37: cpu.uart_buffer.buf37 = c; break;
case 38: cpu.uart_buffer.buf38 = c; break;
case 39: cpu.uart_buffer.buf39 = c; break;
case 40: cpu.uart_buffer.buf40 = c; break;
case 41: cpu.uart_buffer.buf41 = c; break;
case 42: cpu.uart_buffer.buf42 = c; break;
case 43: cpu.uart_buffer.buf43 = c; break;
case 44: cpu.uart_buffer.buf44 = c; break;
case 45: cpu.uart_buffer.buf45 = c; break;
case 46: cpu.uart_buffer.buf46 = c; break;
case 47: cpu.uart_buffer.buf47 = c; break;
case 48: cpu.uart_buffer.buf48 = c; break;
case 49: cpu.uart_buffer.buf49 = c; break;
case 50: cpu.uart_buffer.buf50 = c; break;
case 51: cpu.uart_buffer.buf51 = c; break;
case 52: cpu.uart_buffer.buf52 = c; break;
case 53: cpu.uart_buffer.buf53 = c; break;
case 54: cpu.uart_buffer.buf54 = c; break;
case 55: cpu.uart_buffer.buf55 = c; break;
case 56: cpu.uart_buffer.buf56 = c; break;
case 57: cpu.uart_buffer.buf57 = c; break;
case 58: cpu.uart_buffer.buf58 = c; break;
case 59: cpu.uart_buffer.buf59 = c; break;
case 60: cpu.uart_buffer.buf60 = c; break;
case 61: cpu.uart_buffer.buf61 = c; break;
case 62: cpu.uart_buffer.buf62 = c; break;
case 63: cpu.uart_buffer.buf63 = c; break;

    }
}

void uart_tick() {
    //bool rx_ip = false;

    if ((cpu.clock & 0xff) == 0xff) {
        if (cpu.uart.input_tag != _UdonUARTInTag && UART_GET1(RBR) == 0) {
            cpu.uart.input_tag = _UdonUARTInTag;
            if (_UdonUARTInChar != 0) {
                UART_SET1(RBR, _UdonUARTInChar);
                UART_SET2(LSR, (UART_GET2(LSR) | LSR_DATA_AVAILABLE));
                uart_update_iir();
                //if ((UART_GET1(IER) & IER_RXINT_BIT) != 0) {
                //    rx_ip = true;
                //}
            }
        }
    }

    uint thr = UART_GET1(THR);
    if (thr != 0) {
        put_byte_to_fb(thr);
        UART_SET1(THR, 0);
        UART_SET2(LSR, (UART_GET2(LSR) | LSR_THR_EMPTY));
        uart_update_iir();
        if ((UART_GET1(IER) & IER_THREINT_BIT) != 0) {
            cpu.uart.thre_ip = true;
        }
    }

    // if (!cpu.uart.interrupting && (cpu.uart.thre_ip || rx_ip)) {
    //     cpu.uart.interrupting = true;
    //     cpu.uart.thre_ip = false;
    // } else {
    //     cpu.uart.interrupting = false;
    // }
}

#endif
