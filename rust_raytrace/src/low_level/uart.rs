pub fn print_char(ch: u8) {
    unsafe {
        let thr = 0x10000000 as *mut u8;
        let lsr = 0x10000005 as *mut u8;
        while thr.read_volatile() != 0 || (lsr.read_volatile() & 0x20) == 0 {}
        thr.write_volatile(ch);
    }
}
