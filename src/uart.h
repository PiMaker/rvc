#ifndef UART_H
#define UART_H

#include <stdio.h>
#include "types.h"

static uint uart_input_value = 0;

const uint SHIFT_RBR = 0;
const uint SHIFT_THR = 8;
const uint SHIFT_IER = 16;
const uint SHIFT_IIR = 24;
const uint SHIFT_LCR = 0;
const uint SHIFT_MCR = 8;
const uint SHIFT_LSR = 16;
const uint SHIFT_SCR = 24;

#define UART_GET1(x) ((cpu->uart.rbr_thr_ier_iir >> SHIFT_##x) & 0xff)
#define UART_GET2(x) ((cpu->uart.lcr_mcr_lsr_scr >> SHIFT_##x) & 0xff)

#define UART_SET1(x, val) cpu->uart.rbr_thr_ier_iir = (cpu->uart.rbr_thr_ier_iir & ~(0xff << SHIFT_##x)) | (val << SHIFT_##x)
#define UART_SET2(x, val) cpu->uart.lcr_mcr_lsr_scr = (cpu->uart.lcr_mcr_lsr_scr & ~(0xff << SHIFT_##x)) | (val << SHIFT_##x)

const uint IER_RXINT_BIT = 0x1;
const uint IER_THREINT_BIT = 0x2;

const uint IIR_THR_EMPTY = 0x2;
const uint IIR_RD_AVAILABLE = 0x4;
const uint IIR_NO_INTERRUPT = 0x7;

const uint LSR_DATA_AVAILABLE = 0x1;
const uint LSR_THR_EMPTY = 0x20;

void uart_update_iir(cpu_t *cpu) {
    bool rx_ip = (UART_GET1(IER) & IER_RXINT_BIT) != 0 && UART_GET1(RBR) != 0;
    bool thre_ip = (UART_GET1(IER) & IER_THREINT_BIT) != 0 && UART_GET1(THR) == 0;
    UART_SET1(IIR, (rx_ip ? IIR_RD_AVAILABLE : (thre_ip ? IIR_THR_EMPTY : IIR_NO_INTERRUPT)));
}

void uart_tick(cpu_t *cpu) {
    bool rx_ip = false;

    if ((cpu->clock % 0x38400) == 0 && UART_GET1(RBR) == 0) {
        uint value = uart_input_value; // TODO: Add actual input logic
        uart_input_value = 0;
        if (value != 0) {
            UART_SET1(RBR, value);
            UART_SET2(LSR, (UART_GET2(LSR) | LSR_DATA_AVAILABLE));
            uart_update_iir(cpu);
            if ((UART_GET1(IER) & IER_RXINT_BIT) != 0) {
                rx_ip = true;
            }
        }
    }

    uint thr = UART_GET1(THR);
    if ((cpu->clock & 0x16) == 0 && thr != 0) {
        printf("%c", (char)thr);
        fflush(stdout);
        UART_SET1(THR, 0);
        UART_SET2(LSR, (UART_GET2(LSR) | LSR_THR_EMPTY));
        uart_update_iir(cpu);
        if ((UART_GET1(IER) & IER_THREINT_BIT) != 0) {
            cpu->uart.thre_ip = true;
        }
    }

    if (cpu->uart.thre_ip || rx_ip) {
        cpu->uart.interrupting = true;
        cpu->uart.thre_ip = false;
    } else {
        cpu->uart.interrupting = false;
    }
}

#endif
