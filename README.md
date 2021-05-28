# rvc - risc v in c

An experimental 32-bit [0] RISC-V emulator written in plain C [1], with a focus on porting the result to a HLSL pixel shader.

Mostly based on [takahirox/riscv-rust](https://github.com/takahirox/riscv-rust), which is a great resource for learning about RISC-V in general, aside from the [official specs](https://riscv.org/technical/specifications/) of course.

[0] GPUs only really support 32-bit integer math (in the use-case I want to put this in anyway)  
[1] The elf loader ('elfy') is written in Rust, because I was too lazy to do it myself in C (Rust uses the 'elf' crate) and it doesn't need porting anyway.

# Why?

Because.

# License

MIT. Take it or leave it.
