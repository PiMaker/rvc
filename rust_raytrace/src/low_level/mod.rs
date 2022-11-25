use core::panic::PanicInfo;
use linked_list_allocator::LockedHeap;
use super::output::*;

pub mod uart;

#[naked]
#[no_mangle]
#[link_section = ".start_here"]
#[allow(dead_code)]
/// The actual entry point of the binary, sets up stack and jumps to 'main'
extern "C" fn _start() -> ! {
    unsafe {
        asm!(
            "
                csrr t0, 0xf14
                la sp, {end_stack}
                li t2, 4096
                mul t1, t0, t2
                sub sp, sp, t1
                j main
            ",
            end_stack = sym _end_stack,
            options(noreturn)
        );
    }
}

#[alloc_error_handler]
fn alloc_error(_layout: core::alloc::Layout) -> ! {
    println("ALLOC ERROR!");
    loop {}
}

#[panic_handler]
fn panic(_info: &PanicInfo) -> ! {
    println("PANIC!");
    unsafe { asm! { "ebreak" } }
    loop {}
}

// defined by linker script
extern "C" {
    static _end_stack: usize;
    static _begin_heap: usize;
    static _end_heap: usize;
}

// not actually safe between harts, but shouldn't be used so ignore?
#[global_allocator]
static ALLOCATOR: LockedHeap = LockedHeap::empty();

#[inline(always)]
pub fn hartid() -> usize {
    let hartid: usize;
    unsafe { asm!("csrrs {0}, {1}, x0", out(reg) hartid, const 0xf14); }
    return hartid;
}

pub unsafe fn init_heap() {
    let stack_end = &_end_stack as *const usize as usize;
    let heap_start = stack_end + hartid() * 4096;
    let heap_end = &_end_heap as *const usize as usize;
    let heap_end = heap_end.min(heap_start + 4096);
    let heap_size = heap_end - heap_start;

    print("> stack_end(sym): ");
    print_usize(stack_end);
    print("\n> heap_start:     ");
    print_usize(heap_start);
    print("\n> heap_end:       ");
    print_usize(heap_end);
    print("\n> heap_size:      ");
    print_usize(heap_size);
    print("\n");

    ALLOCATOR.lock().init(heap_start, heap_size);
}
