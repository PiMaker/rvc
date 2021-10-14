use core::panic::PanicInfo;
use linked_list_allocator::LockedHeap;

mod uart;
pub use uart::*;

#[naked]
#[no_mangle]
#[link_section = ".start_here"]
#[allow(dead_code)]
/// The actual entry point of the binary, sets up stack and jumps to 'main'
extern "C" fn _start() -> ! {
    unsafe {
        asm!(
            "
                la sp, {end_stack}
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
    loop {}
}

// defined by linker script
extern "C" {
    static _end_stack: usize;
    static _begin_heap: usize;
    static _end_heap: usize;
}

#[global_allocator]
static ALLOCATOR: LockedHeap = LockedHeap::empty();

pub unsafe fn init_heap() {
    let stack_end = &_end_stack as *const usize as usize;
    let heap_start = &_begin_heap as *const usize as usize;
    let heap_end = &_end_heap as *const usize as usize;
    let heap_size = heap_end - heap_start;

    print("> stack_end:   ");
    print_usize(stack_end);
    print("\n> heap_start:  ");
    print_usize(heap_start);
    print("\n> heap_end:    ");
    print_usize(heap_end);
    print("\n> heap_size:   ");
    print_usize(heap_size);
    print("\n");

    ALLOCATOR.lock().init(heap_start, heap_size);
}
