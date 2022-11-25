use super::text::print_char;

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
        10 => print("a"),
        11 => print("b"),
        12 => print("c"),
        13 => print("d"),
        14 => print("e"),
        15 => print("f"),
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
