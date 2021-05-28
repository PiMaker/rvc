#!/bin/bash

echo "==== Building rvc ===="
make clean
intercept-build make

function run_test {
    pushd ./riscv-tests/isa

    # rm "$1"
    # rm "$1.text"
    make "$1"

    # riscv64-unknown-elf-objcopy -j .text.init -O binary "$1" "$1.text"

    popd

    timeout 5s ./rvc "./riscv-tests/isa/$1"

    if [ $? -gt 0 ]; then
        echo "Test failed!"
        exit $?
    fi
}

if [ "$1" == "all" ]; then
    TESTS="rv32ui-p-add
rv32ui-p-addi
rv32ui-p-and
rv32ui-p-andi
rv32ui-p-auipc
rv32ui-p-beq
rv32ui-p-bge
rv32ui-p-bgeu
rv32ui-p-blt
rv32ui-p-bltu
rv32ui-p-bne
rv32ui-p-fence_i
rv32ui-p-jal
rv32ui-p-jalr
rv32ui-p-lb
rv32ui-p-lbu
rv32ui-p-lh
rv32ui-p-lhu
rv32ui-p-lui
rv32ui-p-lw
rv32ui-p-or
rv32ui-p-ori
rv32ui-p-sb
rv32ui-p-sh
rv32ui-p-simple
rv32ui-p-sll
rv32ui-p-slli
rv32ui-p-slt
rv32ui-p-slti
rv32ui-p-sltiu
rv32ui-p-sltu
rv32ui-p-sra
rv32ui-p-srai
rv32ui-p-srl
rv32ui-p-srli
rv32ui-p-sub
rv32ui-p-sw
rv32ui-p-xor
rv32ui-p-xori
rv32um-p-div
rv32um-p-divu
rv32um-p-mul
rv32um-p-mulh
rv32um-p-mulhsu
rv32um-p-mulhu
rv32um-p-rem
rv32um-p-remu
#rv32ua-p-amoadd_w
#rv32ua-p-amoand_w
#rv32ua-p-amomaxu_w
#rv32ua-p-amomax_w
#rv32ua-p-amominu_w
#rv32ua-p-amomin_w
#rv32ua-p-amoor_w
#rv32ua-p-amoswap_w
#rv32ua-p-amoxor_w
#rv32mi-p-mcsr
#rv32mi-p-csr
#rv32si-p-csr"
    for t in $TESTS; do
        if [[ "$t" =~ ^# ]]; then continue; fi
        echo
        echo "==== TEST: $t ===="
        echo
        run_test "$t"
    done

    echo
    echo "All tests done!"
elif [ -n "$1" ]; then
    run_test "$1"
else
    echo "./test.sh (all|rv32ui-p-foo...)"
fi
