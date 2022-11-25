use super::math::Color;

const RAM_BASE: u32 = 0x80000000;
const FB_START: u32 = 0x80000;
pub const FB_WIDTH: u32 = 2048;
pub const FB_HEIGHT: u32 = 2048 - 32 /* progmem */ - 128 /* CPU state */;
pub const FB_HEIGHT_SLICE: u32 = 224; // FB_HEIGHT / 8

#[inline(always)]
/// accelerated "big" pixel drawing, superscale is size of pixel, forces stall
pub unsafe fn write_px_memop(x: u32, y: u32, col: Color, superscale: u32) {
    let bits: u32 = col.r * 0xffffff;
    asm!("csrrw x0, {1}, {0}", in(reg) bits, const 0x0b3); // CSR_MEMOP_R
    let bits: u32 = col.g * 0xffffff;
    asm!("csrrw x0, {1}, {0}", in(reg) bits, const 0x0b4); // CSR_MEMOP_G
    let bits: u32 = col.b * 0xffffff;
    asm!("csrrw x0, {1}, {0}", in(reg) bits, const 0x0b5); // CSR_MEMOP_B

    let bits: u32 = x | (y << 16);
    asm!("csrrw x0, {1}, {0}", in(reg) bits, const 0x0b1); // CSR_MEMOP_SRC
    let bits: u32 = (x + superscale) | ((y + superscale) << 16);
    asm!("csrrw x0, {1}, {0}", in(reg) bits, const 0x0b2); // CSR_MEMOP_DST

    let bits: u32 = 1;
    asm!("csrrw x0, {1}, {0}", in(reg) bits, const 0x0b0); // CSR_MEMOP_OP
}

#[inline(always)]
/// write a single pixel, unaccelerated, uses main memory but doesn't stall
pub fn write_px_raw(x: u32, y: u32, col: u128) {
    unsafe {
        let ptr = (FB_START + RAM_BASE) as *mut u128;
        let ptr = ptr.add((x + y * FB_WIDTH) as usize);
        ptr.write(col);
    }
}
