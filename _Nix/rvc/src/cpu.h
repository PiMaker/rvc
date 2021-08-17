#ifndef CPU_H
#define CPU_H

cpu_t cpu_init() {
    cpu_t ret = (cpu_t)0;

    ret.xreg11 = 0x1020; // linux? device tree?
    ret.pc = 0x80000000;
    ret.reservation_en = false;

    ret.uart.rbr_thr_ier_iir = 0x00000000;
    ret.uart.lcr_mcr_lsr_scr = 0x00200000; // LSR_THR_EMPTY is set

    ret.csr.privilege = 3; // PRIV_MACHINE

    return ret;
}

void cpu_tick() {
    // DEBUG: single stepping
    if (_DoTick && _DoTick == cpu.debug_do_tick) {
        return;
    }
    cpu.debug_do_tick = _DoTick;

    /* cpu.debug_arb_0 = */
    /* cpu.debug_arb_1 = */
    /* cpu.debug_arb_2 = */
    /* cpu.debug_arb_3 = */
    /* cpu.debug_arb_4 = */
    /* cpu.debug_arb_5 = */
    /* cpu.debug_arb_6 = */
    /* cpu.debug_arb_7 = 0; */

    cpu.clock++;
    emulate();

    /* if ((_BreakpointClock && _BreakpointClock == cpu.clock) || (_Breakpoint && _Breakpoint == cpu.pc)) { */
    /*     cpu.debug_do_tick = 0xffffffff; */
    /*     _DoTick = cpu.debug_do_tick; */
    /* } */

    if (cpu.stall) {
        cpu.stall_count++;
        return;
    }
}

#endif
