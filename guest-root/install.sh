#!/bin/sh

BUILDROOT="buildroot-2022.02.1"

set -e

# target directory
Q=$1

# enter current directory
cd ../guest-root

for f in *; do
    if [ "$f" == "install.sh" ]; then continue; fi
    cp -r -v "$f" "$Q"
done

mkdir -p "$Q/tmp/work"
mkdir -p "$Q/tmp/upper"
mkdir -p "$Q/tmp/newroot"

# install beluga
cd ../riscv32_beluga
sed -i 's|$(CC) -o $S/ecgen|$(HOSTCC) -o $S/ecgen|' bcc/Makefile
make clean
make -j1 CC=$PWD/../$BUILDROOT/output/host/bin/riscv32-buildroot-linux-gnu-gcc HOSTCC=gcc
cd ..
mkdir -p $BUILDROOT/output/target/usr/local/bin
cp riscv32_beluga/build/{bcc,beluga} $BUILDROOT/output/target/usr/local/bin
# ln -s libc.so.6 $(BUILDROOT)/output/target/lib32/libc.so || true
# ln -s libm.so.6 $(BUILDROOT)/output/target/lib32/libm.so || true
# cp riscv32_beluga/riscvbin/bin/{as,ld,ar,dof} $(BUILDROOT)/output/target/usr/local/bin
mkdir -p $BUILDROOT/output/target/usr/local/lib32/bcc
cp riscv32_beluga/build/xfloat.o $BUILDROOT/output/target/usr/local/lib32/bcc/
cp -Lr riscv32_beluga/build/include $BUILDROOT/output/target/usr/local/lib32/bcc/
cp riscv32_beluga/riscvbin/ar/libc.a $BUILDROOT/output/target/usr/local/lib32/
cp $BUILDROOT/output/host/lib/gcc/riscv32-buildroot-linux-gnu/11.2.0/libgcc.a $BUILDROOT/output/target/usr/local/lib32/
cp $BUILDROOT/output/host/lib/gcc/riscv32-buildroot-linux-gnu/11.2.0/libgcc_eh.a $BUILDROOT/output/target/usr/local/lib32/

