#![no_std]
#![no_main]
#![feature(asm)]
#![feature(naked_functions)]
#![feature(alloc_error_handler)]

#[macro_use]
extern crate alloc;

mod low_level;
use low_level::*;

use riscv::register;

#[no_mangle]
pub fn main() -> ! {
    print("\n");

    println("Welcome to Rust-land!");

    print("Cycles before: ");
    print_usize(register::time::read());
    print("\n\n");

    println("Initializing heap...");
    unsafe {
        init_heap();
    }
    print("\n");

    // input_test();
    // print("\n");

    json_test();
    print("\n");

    print("Cycles after: ");
    print_usize(register::time::read());
    print("\n");

    println("Tests done, entering infinite loop!");
    loop {}
}

/// Test opensbi uart input
fn input_test() {
    print("Please enter some text: ");
    let mut s = vec![];
    loop {
        let i = loop {
            let i = ecall(SBI_CONSOLE_GETCHAR, 0, 0, 0);
            if i != 0 && i != usize::MAX {
                break i as u8 as char;
            }
        };

        match i {
            '\n' => break,
            _ => s.push(i as u8)
        }
    }
    print("Your text was: ");
    for c in s {
        print_char(c);
    }
    print("\n");
}

/// From lite-json docs, a simple example to showcase functionality
fn json_test() {
    use lite_json::json::{JsonValue, NumberValue};
    use lite_json::Serialize;

    println("Preparing JSON test...");

    let mut object_elements = vec![];

    let boolean_value = true;
    let object_key = "boolean".chars().collect();
    object_elements.push((object_key, JsonValue::Boolean(boolean_value)));

    let array_value = vec![
        JsonValue::Boolean(true),
        JsonValue::Boolean(false),
        JsonValue::Boolean(true),
    ];
    let object_key = "array".chars().collect();
    object_elements.push((object_key, JsonValue::Array(array_value)));

    let string_value = "Hello World!".chars().collect();
    let object_key = "string".chars().collect();
    object_elements.push((object_key, JsonValue::String(string_value)));

    let number_value = NumberValue {
        integer: 1234,
        fraction: 0,
        fraction_length: 0,
        exponent: 0,
    };
    let object_key = "number".chars().collect();
    object_elements.push((object_key, JsonValue::Number(number_value)));

    let object_key = "null".chars().collect();
    object_elements.push((object_key, JsonValue::Null));

    let object_value = JsonValue::Object(object_elements);

    println("JSON dump:");

    let json = object_value.format(2);
    for x in json {
        print_char(x as u8);
    }

    print("\n");
}

