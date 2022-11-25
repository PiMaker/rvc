use std::env;
use std::path::PathBuf;
use std::io::prelude::*;
use std::fs::File;

use image::io::Reader as ImageReader;

fn main2() {
    let args: Vec<String> = env::args().collect();
    let input = &args[1];
    let addr = &args[2].parse::<u32>().unwrap();

    let fr = ImageReader::open(format!("{}.r.bmp", input)).unwrap().decode().unwrap();
    let fr = fr.into_rgba8();
    let fg = ImageReader::open(format!("{}.g.bmp", input)).unwrap().decode().unwrap();
    let fg = fg.into_rgba8();
    let fb = ImageReader::open(format!("{}.b.bmp", input)).unwrap().decode().unwrap();
    let fb = fb.into_rgba8();
    let fa = ImageReader::open(format!("{}.a.bmp", input)).unwrap().decode().unwrap();
    let fa = fa.into_rgba8();

    let addr = addr & !(0x3);
    let idx = (addr >> 2) & 0x3;
    let addr = addr >> 4;
    let (x, y) = (addr & fr.width(), addr / fr.width());
    let px = match idx {
        0 => fr.get_pixel(x, y),
        1 => fg.get_pixel(x, y),
        2 => fb.get_pixel(x, y),
        3 => fa.get_pixel(x, y),
        _ => unimplemented!(),
    };

    let res = ((px.0[0] as u32) << 0) |
              ((px.0[1] as u32) << 8) |
              ((px.0[2] as u32) << 16) |
              ((px.0[3] as u32) << 24);

    println!("r={} g={} b={} a={}", px.0[0] as u32, px.0[1] as u32, px.0[2] as u32, px.0[3] as u32);

    println!("x{} y{} i{} => {:#x}", x, y, idx, res);
}

fn main() {
    let args: Vec<String> = env::args().collect();
    let input = PathBuf::from(&args[1]);
    let width = args[2].parse::<u32>().unwrap();
    let height = args[3].parse::<u32>().unwrap();

    let file = File::open(&input).unwrap().bytes();

    let mut fr = image::ImageBuffer::new(width, height);
    let mut fg = image::ImageBuffer::new(width, height);
    let mut fb = image::ImageBuffer::new(width, height);
    let mut fa = image::ImageBuffer::new(width, height);

    let mut idx_a = 0;
    let mut idx_b = 0;
    let mut idx = 0;

    // for x in 0..width {
    //     for y in 0..height {
    //         for i in 0..4 {
    //             let f = match i {
    //                 0 => &mut fr,
    //                 1 => &mut fg,
    //                 2 => &mut fb,
    //                 3 => &mut fa,
    //                 _ => unreachable!(),
    //             };
    //             let mut cur: &mut image::Rgba<u8> = f.get_pixel_mut(x, y);
    //             cur.0 = [0, 0, 0, 0];
    //         }
    //     }
    // }

    println!("Converting...");
    for b in file {
        if let Ok(b) = b {
            let f = match idx_b {
                0 => &mut fr,
                1 => &mut fg,
                2 => &mut fb,
                3 => &mut fa,
                _ => unreachable!(),
            };

            let x = idx % width;
            let y = idx / width;
            let mut cur: &mut image::Rgba<u8> = f.get_pixel_mut(x, y);

            match idx_a {
                0 => cur.0[0] = b,
                1 => cur.0[1] = b,
                2 => cur.0[2] = b,
                3 => cur.0[3] = b,
                _ => unreachable!(),
            }

            // f.set_pixel(x, y, cur);

            idx_a += 1;
            if idx_a == 4 {
                idx_a = 0;
                idx_b += 1;
                if idx_b == 4 {
                    idx_b = 0;
                    idx += 1;
                }
            }
        }
    }

    let y = idx / width;
    println!("Saving result... (required size: x={} y={})", width, y + 1);
    fr.save(input.clone().with_extension("r.png")).unwrap();
    fg.save(input.clone().with_extension("g.png")).unwrap();
    fb.save(input.clone().with_extension("b.png")).unwrap();
    fa.save(input.clone().with_extension("a.png")).unwrap();
}
