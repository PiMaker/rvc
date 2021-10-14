#![no_std]
#![no_main]
#![feature(asm)]
#![feature(naked_functions)]
#![feature(alloc_error_handler)]

// #[macro_use]
extern crate alloc;

mod low_level;
use low_level::*;

mod raytrace;
use raytrace::*;

mod math;
use math::*;

const RAM_BASE: u32 = 0x80000000;
const FB_START: u32 = 0x80000;
const FB_WIDTH: u32 = 2048;
const FB_HEIGHT: u32 = 2048 - 16 /* progmem */ - 128 /* CPU state */;
// const AA_BORDER: u32 = 10;

static mut SUPERSCALE: u32 = 96; // start at 48
pub fn superscale() -> u32 {
    unsafe { SUPERSCALE }
}

#[no_mangle]
pub fn main() -> ! {
    println("Initializing heap...");
    unsafe {
        init_heap();
    }

    println("Setting up scene...");

    let mut scene = Scene::new();

    scene.add_obj(Plane {
        id: 0,
        position: Vector3 {
            x: 0.0,
            y: 3.0,
            z: 0.0,
        },
        normal: Vector3 {
            x: 0.0,
            y: 1.0,
            z: 0.0,
        },
        color: Color {
            r: 180,
            g: 180,
            b: 200,
        },
    });

    scene.add_obj(Sphere {
        id: 1,
        center: Vector3 {
            x: 3.5,
            y: 0.0,
            z: 9.0,
        },
        radius: 2.5,
        color: Color {
            r: 166,
            g: 105,
            b: 238,
        },
    });
    scene.add_obj(Sphere {
        id: 2,
        center: Vector3 {
            x: 5.5,
            y: 2.0,
            z: 10.0,
        },
        radius: 3.0,
        color: Color {
            r: 250,
            g: 28,
            b: 137,
        },
    });
    scene.add_obj(Sphere {
        id: 3,
        center: Vector3 {
            x: -4.8,
            y: 3.2,
            z: 8.6,
        },
        radius: 3.8,
        color: Color {
            r: 10,
            g: 240,
            b: 70,
        },
    });
    // mirror sphere
    scene.add_obj(Sphere {
        id: 4,
        center: Vector3 {
            x: 0.0,
            y: -6.0,
            z: 16.0,
        },
        radius: 4.0,
        color: Color {
            r: 255,
            g: 255,
            b: 255,
        },
    });

    scene.add_light(Light {
        position: Vector3 {
            x: -3.0,
            y: -3.8,
            z: -5.5,
        },
        intensity: 0.1,
    });
    scene.add_light(Light {
        position: Vector3 {
            x: 2.9,
            y: -9.8,
            z: 12.0,
        },
        intensity: 0.07,
    });

    while superscale() > 1 {
        unsafe { SUPERSCALE /= 2 };
        print("Tracing @");
        print_usize(superscale() as usize);
        print(" ");

        for y in (0..(FB_HEIGHT / superscale())).rev() {
            for x in 0..(FB_WIDTH / superscale()) {
                // Testpattern:
                // let col = Vector3::new(
                //     if (x % 2) == 0 { 255 } else { 0 },
                //     ((y * 255) / (FB_HEIGHT / superscale())) as i32,
                //     if (y % 2) == 0 { 255 } else { 0 },
                // );
                let col = scene.raytrace(
                    x as i32 - (FB_WIDTH / superscale() / 2) as i32,
                    y as i32 - (FB_HEIGHT / superscale() / 2) as i32,
                );
                write_px(x, y, col);
            }

            print(".");
        }

        // print(" Done!\nAnti-Aliasing");

        // for y in 0..(FB_HEIGHT / superscale()) {
        //     for x in 0..(FB_WIDTH / superscale()) {
        //         // tap neighboring pixels and mix into borders
        //         let cur = read_px_raw(x * superscale() + superscale() / 2, y * superscale() + superscale() / 2);
        //         let top = read_px_raw(x * superscale() + superscale() / 2, y * superscale() - superscale() / 2);
        //         let right = read_px_raw((x + 1) * superscale() + superscale() / 2, y * superscale() + superscale() / 2);
        //         let bottom = read_px_raw(x * superscale() + superscale() / 2, (y + 1) * superscale() + superscale() / 2);
        //         let left = read_px_raw(x * superscale() - superscale() / 2, y * superscale() + superscale() / 2);
        //         for ys in 0..superscale() {
        //             for xs in 0..superscale() {
        //                 let mut cur = cur.clone();
        //                 let mut write = false;
        //                 if xs < AA_BORDER {
        //                     cur.mix_in(&left);
        //                     write = true;
        //                 }
        //                 if xs > (superscale() - AA_BORDER) {
        //                     cur.mix_in(&right);
        //                     write = true;
        //                 }
        //                 if ys < AA_BORDER {
        //                     cur.mix_in(&top);
        //                     write = true;
        //                 }
        //                 if ys > (superscale() - AA_BORDER) {
        //                     cur.mix_in(&bottom);
        //                     write = true;
        //                 }

        //                 if write {
        //                     write_px_raw(x * superscale() + xs, y * superscale() + ys, cur.to_u128());
        //                 }
        //             }
        //         }
        //     }

        //     print(".");
        // }

        println(" Done!");
    }

    print("Program finished.");

    loop {}
}

fn write_px(x: u32, y: u32, col: Color) {
    let col = col.to_u128();
    let x = x * superscale();
    let y = y * superscale();

    for ys in 0..superscale() {
        for xs in 0..superscale() {
            write_px_raw(x + xs, y + ys, col);
        }
    }
}

fn write_px_raw(x: u32, y: u32, col: u128) {
    unsafe {
        let ptr = (FB_START | RAM_BASE) as *mut u128;
        let ptr = ptr.add((x + y * FB_WIDTH) as usize);
        ptr.write(col);
    }
}

// fn read_px_raw(x: u32, y: u32) -> Color {
//     let col: u128;
//     unsafe {
//         let ptr = (FB_START | RAM_BASE) as *mut u128;
//         let ptr = ptr.add((x + y * FB_WIDTH) as usize);
//         col = ptr.read();
//     }
//     Color {
//         r: (((col >> 0) & 0xffffffff) / 0xffffff) as u32,
//         g: (((col >> 32) & 0xffffffff) / 0xffffff) as u32,
//         b: (((col >> 64) & 0xffffffff) / 0xffffff) as u32,
//     }
// }
