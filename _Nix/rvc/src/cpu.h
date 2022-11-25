#ifndef CPU_H
#define CPU_H

cpu_t cpu_init() {
    cpu_t ret = (cpu_t)0;

    ret.xreg[11] = 0x1020; // device tree base
    ret.pc = 0x80000000;
    ret.reservation_en = false;

    ret.uart.rbr_thr_ier_iir = 0x00000000;
    ret.uart.lcr_mcr_lsr_scr = 0x00200000; // LSR_THR_EMPTY is set

    ret.csr.privilege = 3; // PRIV_MACHINE

    ret.start_time_ref = _Time.y;

    return ret;
}

void cpu_tick() {
    // DEBUG: single stepping
    if (_DoTick && _DoTick == cpu.debug_do_tick) {
        return;
    }
    cpu.debug_do_tick = _DoTick;

    cpu.clock++;
    emulate();

    /* if ((_BreakpointClock && _BreakpointClock == cpu.clock) || (_Breakpoint && _Breakpoint == cpu.pc)) { */
    /*     cpu.debug_do_tick = 0xffffffff; */
    /*     _DoTick = cpu.debug_do_tick; */
    /* } */

    if (cpu.stall) {
        cpu.stall_count++;
    }
}

#endif
