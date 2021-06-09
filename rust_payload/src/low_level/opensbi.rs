pub const _SBI_SET_TIMER: usize = 0x00;
pub const SBI_CONSOLE_PUTCHAR: usize = 0x01;
pub const SBI_CONSOLE_GETCHAR: usize = 0x02;

#[inline(always)]
pub fn ecall(nr: usize, arg0: usize, arg1: usize, arg2: usize) -> usize {
    let ret: usize;
    unsafe {
        asm!(
            "ecall",
            in("x17") nr,
            in("x10") arg0,
            in("x11") arg1,
            in("x12") arg2,
            lateout("x10") ret
        );
    }
    ret
}

#[inline(always)]
pub fn print_char(ch: u8) {
    ecall(SBI_CONSOLE_PUTCHAR, ch as usize, 0, 0);
}

pub fn println(s: &str) {
    print(s);
    print_char('\n' as u8);
}

pub fn print(s: &str) {
    s.chars().for_each(|c| print_char(c as u8));
}

#[inline(always)]
fn print_hex_part(u: u8) {
    match u {
        0 => print("0"),
        1 => print("1"),
        2 => print("2"),
        3 => print("3"),
        4 => print("4"),
        5 => print("5"),
        6 => print("6"),
        7 => print("7"),
        8 => print("8"),
        9 => print("9"),
        10 => print("A"),
        11 => print("B"),
        12 => print("C"),
        13 => print("D"),
        14 => print("E"),
        15 => print("F"),
        _ => unreachable!(),
    }
}

pub fn print_usize(u: usize) {
    print("0x");
    for i in 0..=3 {
        let part = ((u >> ((3 - i) * 8)) & 0xff) as u8;
        let l = part & 0xF;
        let h = (part >> 4) & 0xF;
        print_hex_part(h);
        print_hex_part(l);
    }
}
