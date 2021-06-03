use std::ffi::{CStr, OsStr};
use std::path::PathBuf;
use std::os::unix::ffi::OsStrExt;
use std::os::raw::c_char;

#[no_mangle]
pub extern "C" fn load_elf(path: *const c_char, path_len: u64, data: *mut u8, data_len: u64, verbose: bool) -> i32 {
    let res = std::panic::catch_unwind(|| {
        do_load_elf(path, path_len, data, data_len, verbose);
    });
    match res {
        Ok(()) => 0,
        _ => 1,
    }
}

fn do_load_elf(path: *const c_char, path_len: u64, data: *mut u8, data_len: u64, verbose: bool) {
    let path = unsafe { CStr::from_bytes_with_nul_unchecked(std::slice::from_raw_parts(path as *const u8, path_len as usize)) };
    let path = OsStr::from_bytes(path.to_bytes());
    let path = PathBuf::from(path);

    if verbose {
        println!("Loading ELF binary '{}'", path.display());
    }

    let elf = elf::File::open_path(path).unwrap();

    for section in elf.sections {
        if section.shdr.shtype.0 != 1 {
            continue;
        }

        let name = section.shdr.name;
        let addr = section.shdr.addr;
        let addr_real = addr & 0x7FFFFFFF;
        let size = section.data.len() as u64;

        if name == ".comment" {
            if verbose {
                let comment = String::from_utf8_lossy(&section.data);
                println!("ELF comment: {}", comment);
            }
            continue;
        }

        if addr == 0 {
            if verbose {
                println!("Skipping 'zero address' ELF section '{}' @{:#x} (@{:#x}) size={}", name, addr, addr_real, size);
            }
            continue;
        }

        if verbose {
            println!("Loading ELF section '{}' @{:#x} (@{:#x}) size={}", name, addr, addr_real, size);
        }

        if addr_real + size > data_len {
            panic!("ELF section too big or offset to great");
        }

        let mut i = 0;
        for byte in section.data {
            unsafe { std::ptr::write(data.add(addr_real as usize + i), byte) };
            i += 1;
        }
    }
}
