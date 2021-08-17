#ifndef TYPES_H
#define TYPES_H

<?:include header.p ?>

#define STALL_EXIT_CALL 1
#define STALL_CSR_CACHE 2
#define STALL_MEM_CACHE_L1 3
#define STALL_MEM_CACHE_L2 4
#define STALL_ILLEGAL_ENTRY_POINT 5
#define STALL_UART 6
#define STALL_FENCE 7
#define STALL_MEMOP_COPY 8

<?

my $width = 128;
my $height = 128;
my $total_width = 2048;
my $total_height = 2048;

my $state = {};
my $addr = 0;
my $s = sub {
    my ($type, $name, $def) = @_;
    $state->{$name} = {
        name => $name,
        type => $type,
        addr => $addr,
        def => $def,
    };
    $addr++;
    if ($name =~ m/.*\.(.*)$/) {
        print "$type $1;";
    } else {
        print "$type $name;";
    }
};

my $d = sub {
    if (0) { # enable for DEBUG
        $s->(@_);
    }
};

?>

// STRUCT TYPES
typedef struct {
    <? 
    for my $i (0..$csr_cache_max) {
        $s->("uint", "cache.csr_cache_${i}_addr", 0xffffffff);
        print " ";
        $s->("uint", "cache.csr_cache_${i}_val", 0xdeadc7de);
        print "\n    ";
    }

    for my $i (0..$ram_l1_set_max) {
        for my $j (0..$ram_l1_line_max) {
            my $ci = $i + $j * ($ram_l1_set_max + 1);
            $s->("uint", "cache.ram_l1_${ci}_addr", 0xffffffff);
            print " ";
            $s->("uint", "cache.ram_l1_${ci}_val", 0xdeadc8de);
            print "\n    ";
        }
    }

    $s->("uint", "cache.ram_l1_last_addr", 0xffffffff);
    $s->("uint", "cache.ram_l1_last_val", 0xdeadc9de);
    ?>
} cache_t;

typedef struct {
    <? $s->("uint", "csr.privilege"); ?>
} csr_state;

typedef struct {
    <? $s->("uint", "uart.rbr_thr_ier_iir"); ?>
    <? $s->("uint", "uart.lcr_mcr_lsr_scr"); ?>
    <? $s->("bool", "uart.thre_ip"); ?>
    <? $s->("bool", "uart.interrupting"); ?>
    <? $s->("uint", "uart.input_tag"); ?>
} uart_state;

typedef struct {
    <? $s->("bool", "clint.msip"); ?>
    <? $s->("uint", "clint.mtimecmp_lo"); ?>
    <? $s->("uint", "clint.mtimecmp_hi"); ?>
    <? $s->("uint", "clint.mtime_lo"); ?>
    <? $s->("uint", "clint.mtime_hi"); ?>
} clint_state;

typedef struct {
    <? $s->("uint", "uart_buffer.ptr"); ?>
    <?
    for my $i (0..$uart_buffer_max) {
        $s->("uint", "uart_buffer.buf${i}");
        print "\n    ";
    }
    ?>
} uart_buffer;

typedef struct {
    <? $s->("uint", "mmu.mode"); ?>
    <? $s->("uint", "mmu.ppn"); ?>
} mmu_state;

typedef struct {
    <? $s->("uint", "stall"); ?>
    <? $s->("uint", "clock"); ?>
    <? $s->("uint", "commits"); ?>
    <? for my $i (0..31) {
        $s->("uint", "xreg$i");
        print "\n    ";
    } ?>
    <? $s->("uint", "pc"); ?>
    csr_state csr;
    clint_state clint;
    uart_state uart;
    uart_buffer uart_buffer;
    mmu_state mmu;

    <? $s->("bool", "reservation_en"); ?>
    <? $s->("uint", "reservation_addr"); ?>

    <? $s->("uint", "memop_src_v"); ?>
    <? $s->("uint", "memop_dst_v"); ?>
    <? $s->("uint", "memop_src_p"); ?>
    <? $s->("uint", "memop_dst_p"); ?>
    <? $s->("uint", "memop_n"); ?>

    <? $s->("uint", "stall_count"); ?>
    <? $s->("uint", "trap_count"); ?>

    <? $s->("uint", "debug_do_tick"); ?>
    <? $s->("uint", "debug_last_ins"); ?>
    <? $s->("uint", "debug_last_stall"); ?>
    <? $d->("uint", "debug_csr_val"); ?>
    <? $d->("uint", "debug_mem_val"); ?>

    <? $s->("uint", "debug_arb_0"); ?>
    <? $d->("uint", "debug_arb_1"); ?>
    <? $d->("uint", "debug_arb_2"); ?>
    <? $d->("uint", "debug_arb_3"); ?>
    <? $d->("uint", "debug_arb_4"); ?>
    <? $d->("uint", "debug_arb_5"); ?>
    <? $d->("uint", "debug_arb_6"); ?>
    <? $d->("uint", "debug_arb_7"); ?>

    cache_t cache;
} cpu_t;

typedef struct {
    bool en;
    bool irq;
    uint type;
    uint value;
} trap;

typedef struct {
    uint write_reg;
    uint write_val;
    uint pc_val;
    uint csr_write;
    uint csr_val;
    uint mem_wr_addr;
    uint mem_wr_value;
    uint mem_wr_size;
    trap trap;
} ins_ret;

// GLOBAL STATICS
static cpu_t cpu;

// TYPE HELPERS
ins_ret ins_ret_noop() {
    ins_ret ret = (ins_ret)0;
    ret.pc_val = cpu.pc + 4;
    return ret;
}

uint sign_extend(uint x, uint b) {
    uint m = ((uint)1) << (b - 1);
    return (x ^ m) - m;
}

uint xreg(uint i) {
    #define C(x) case x: return cpu.xreg##x;
    if (i < 16) {
        [flatten]
        switch (i) {
            C(0) C(1) C(2) C(3)
            C(4) C(5) C(6) C(7)
            C(8) C(9) C(10) C(11)
            C(12) C(13) C(14) C(15)
        }
    } else {
        [flatten]
        switch (i) {
            C(16) C(17) C(18) C(19)
            C(20) C(21) C(22) C(23)
            C(24) C(25) C(26) C(27)
            C(28) C(29) C(30) C(31)
        }
    }
    return 0xdeadc0de;
    #undef C
}

// ENCODE/DECODE LOGIC (state serialization into self texture)

<?

my $addr_lin = sub {
    my ($lin) = @_;
    my $col = $lin & 0x3;
    $lin = ($lin & (~0x3)) >> 2;
    return {
        x => $lin % $width,
        y => int($lin / $width),
        c => $col,
    };
};

my $addr_id = sub {
    my ($lin) = @_;
    my $a = $addr_lin->($lin);
    return $a->{x} | ($a->{y} << 16);
};

my $rev = {};
for my $prop (keys %$state) {
    my $aid = $addr_id->($state->{$prop}->{addr});
    $rev->{$aid}->{$prop} = $state->{$prop};
}

?>

void decode(uint udonUartPtr) {
    cpu = (cpu_t)0;

<?
    for my $prop (sort { $state->{$a}->{addr} <=> $state->{$b}->{addr} } keys %$state) {
        my $n = $state->{$prop}->{name};
        my $a = $addr_lin->($state->{$prop}->{addr});
        my $t = $state->{$prop}->{type};

        if (defined($state->{$prop}->{def})) {
            print "    cpu.$n = $t($state->{$prop}->{def});\n";
        } else {
            print "    cpu.$n = $t(idx_uint4(STATE_TEX[uint2($a->{x}, $a->{y})], $a->{c}));\n";
        }
    }
?>

    if (cpu.stall == STALL_UART && udonUartPtr == cpu.uart_buffer.ptr) {
        cpu.stall = 0;
    }
}

#ifdef PASS_COMMIT
void decode_for_commit() {
    cpu = (cpu_t)0;

<?
    for my $prop (sort { $state->{$a}->{addr} <=> $state->{$b}->{addr} } keys %$state) {
        my $n = $state->{$prop}->{name};
        my $a = $addr_lin->($state->{$prop}->{addr});
        my $t = $state->{$prop}->{type};

        # for committing only the L1 RAM and CSR caches are important
        # (not anymore?)
        # next if !($prop =~ m/cache\.ram/ || $prop =~ m/cache\.csr/);

        print "    cpu.$n = $t(idx_uint4(STATE_TEX[uint2($a->{x}, $a->{y})], $a->{c}));\n";
    }
?>
}
#endif

bool pixel_has_state(uint2 pos) {
    <?
    my $a_max = $addr_lin->($addr);
    ?>
    return pos.y < <?= $a_max->{y} ?> || (pos.y == <?= $a_max->{y} ?> && pos.x <= <?= $a_max->{x} ?>);
}

<?
my $csr_cache_start = ($addr + 3) & (~0x3); # account for idx shift (I think)
?>

/* void set_debug_arb() { */
/*     <? for my $arb (0..7) { ?> */
/*     cpu.debug_arb_<?= $arb ?> = cpu.xreg<?= ($arb * 4 + 0) ?> ^ */
/*                                 cpu.xreg<?= ($arb * 4 + 1) ?> ^ */
/*                                 cpu.xreg<?= ($arb * 4 + 2) ?> ^ */
/*                                 cpu.xreg<?= ($arb * 4 + 3) ?>; */
/*     <? } ?> */
/* } */

uint4 encode(uint2 pos) {
    // fallback is passthrough
    uint4 ret = STATE_TEX[pos];

    uint pos_id = pos.x | (pos.y << 16);

    switch (pos_id) {
<?
    for my $aid (sort keys %$rev) {
        print "    case $aid:\n";
        for my $prop (sort keys %{$rev->{$aid}}) {
            my $p = $rev->{$aid}->{$prop};
            my $c = $addr_lin->($p->{addr})->{c};
            $c = ("r", "g", "b", "a")[$c];
            if ($prop eq "stall") {
                print "        ret.$c = uint(cpu.$p->{name} == STALL_CSR_CACHE ? 0 : (cpu.$p->{name} == STALL_MEM_CACHE_L1 ? 0 : cpu.$p->{name}));\n";
            } elsif ($prop eq "debug_last_stall") {
                print "        ret.$c = uint(cpu.stall);\n";
            } else {
                print "        ret.$c = uint(cpu.$p->{name});\n";
            }
        }
        print "        return ret;\n";
    }
?>
    }

    return ret;
}

uint tex_get_csr(uint addr) {
    uint lin = (addr >> 2) + <?= $csr_cache_start ?>;
    uint idx = addr & 0x3;
    return idx_uint4(STATE_TEX[uint2(lin % <?= $width ?>, lin / <?= $height ?>)], idx);
}

<?
# RAM access
print "#define RAM_ADDR(lin) uint2(lin % $total_width, $height + (lin / $total_width))\n";
print "#define RAM_MAX ($total_width * ($total_height - $height) * 4 * 4)\n";
?>

// Memory operations (should be in mem.h but cyclic dependencies...)

// Basic bloom filter to slightly optimize memory caching
#ifdef PASS_TICK
static uint mem_cache_bloom = 0;
#else
static uint mem_cache_bloom = 0xffffffff;
#endif

[noinline] // I'm pretty sure this does nothing, but see it as a prayer to the compiler gods
uint mem_get_cached_or_tex(uint addr) {
    // query L1 cache
    if ((addr & mem_cache_bloom) != addr) { /* not cached */ }
    else {
        [forcecase]
        switch (RAM_L1_TAG(addr)) {
<?
for my $i (0..$ram_l1_set_max) {
    print "case $i:\n";
    for my $j (0..$ram_l1_line_max) {
        my $ci = $i + $j * ($ram_l1_set_max + 1);
        my $e = $j == 0 ? "    " : "else";
        print "$e if (cpu.cache.ram_l1_${ci}_addr == addr) { return cpu.cache.ram_l1_${ci}_val; }\n";
    }
    print "break;\n"
}
?>
        }

        if (cpu.cache.ram_l1_last_addr == addr) {
            return cpu.cache.ram_l1_last_val;
        }
    }

    uint idx = (addr >> 2) & 0x3;
    addr >>= 4;

    uint4 raw = STATE_TEX[RAM_ADDR(addr)];
    return idx_uint4(raw, idx);
}


#ifdef PASS_COMMIT
uint4 commit(uint2 pos) {
    if (pos.y < <?= $height ?> && pos.x >= <?= $width ?>) {
        return (uint4)0;
    }

    // fallback is passthrough
    uint4 ret = STATE_TEX[pos];

    uint pos_id = pos.x | (pos.y << 16);

    // increment commits
    if (!_Init && pos_id == <?= $addr_id->($state->{commits}->{addr}) ?>) {
        ++ret.<? my $c = $addr_lin->($state->{commits}->{addr})->{c}; $c = ("r", "g", "b", "a")[$c]; print $c; ?>;
    }

    // clear stall
    if (pos_id == <?= $addr_id->($state->{stall}->{addr}) ?>) {
        [flatten]
        switch (ret.<? my $c2 = $addr_lin->($state->{stall}->{addr})->{c}; $c2 = ("r", "g", "b", "a")[$c2]; print $c2; ?>) {
            case STALL_MEM_CACHE_L2:
                ret.<?= $c2 ?> = 0;
                break;
            case STALL_FENCE:
                ret.<?= $c2 ?> = 0;
                break;
            case STALL_MEMOP_COPY: // will be handled now, so we can unset
                ret.<?= $c2 ?> = 0;
                break;
        }
    }

    uint s_lin = pos.x + pos.y * <?= $width ?>;

    // CSR area
    if (s_lin >= <?= $csr_cache_start ?> && s_lin < <?= $csr_cache_start + 1024 ?>) {
        uint addr = s_lin - <?= $csr_cache_start ?>;
        addr <<= 2;
<?
        for my $i (0..$csr_cache_max) {
            print "        if      (cpu.cache.csr_cache_${i}_addr == addr + 0) { ret.x = cpu.cache.csr_cache_${i}_val; }\n";
            print "        else if (cpu.cache.csr_cache_${i}_addr == addr + 1) { ret.y = cpu.cache.csr_cache_${i}_val; }\n";
            print "        else if (cpu.cache.csr_cache_${i}_addr == addr + 2) { ret.z = cpu.cache.csr_cache_${i}_val; }\n";
            print "        else if (cpu.cache.csr_cache_${i}_addr == addr + 3) { ret.w = cpu.cache.csr_cache_${i}_val; }\n";
        }
?>
    }

    // RAM
    if (pos.y >= <?= $height ?>) {
        uint2 pos_ram = uint2(pos.x, pos.y - <?= $height ?>);
        uint lin = pos_ram.x + pos_ram.y * <?= $total_width ?>;

        if (_Init) {
            // init main memory from texture
            uint2 ram_dim;
            _Data_RAM_A.GetDimensions(ram_dim.x, ram_dim.y);

            // TODO: something feels off here... off by one, you might say...
            uint2 pos2 = uint2(lin % ram_dim.x, lin / ram_dim.x);
            pos2.y = ram_dim.y - pos2.y - 1;

            if (pos2.y >= ram_dim.y) {
                // zero unset memory
                ret = uint4(0, 0, 0, 0);
            } else {
                uint r = unpack_raw_float4(_Data_RAM_R[pos2]);
                uint g = unpack_raw_float4(_Data_RAM_G[pos2]);
                uint b = unpack_raw_float4(_Data_RAM_B[pos2]);
                uint a = unpack_raw_float4(_Data_RAM_A[pos2]);
                ret = uint4(r, g, b, a);
            }
        } else {
            lin <<= 4;

            if (cpu.stall == STALL_MEMOP_COPY &&
                (lin + (3 << 2)) >= cpu.memop_dst_p &&
                lin < (cpu.memop_dst_p + cpu.memop_n))
            {
                // we've found ourselves in a position for a memcpy, ignore cache and perform it
                // (a memop is always the last instruction in a commit cycle, so we know we have
                // higher priority than the L1 cache)
                [loop]
                for (uint icp = 0; icp < 4; icp++) {
                    uint lin_word = lin + (icp << 2);
                    if (lin_word >= cpu.memop_dst_p &&
                        lin_word < (cpu.memop_dst_p + cpu.memop_n))
                    {
                        uint offset = cpu.memop_dst_p - lin_word;
                        uint src = cpu.memop_src_p + offset;
                        uint transfer = mem_get_cached_or_tex(src);
                        switch (icp) {
                            case 0:
                                ret.r = transfer;
                                break;
                            case 1:
                                ret.g = transfer;
                                break;
                            case 2:
                                ret.b = transfer;
                                break;
                            case 3:
                                ret.a = transfer;
                                break;
                        }
                    }
                }
            }
            else
            {
            // write back L1 cache
<?
            for my $i (0..$ram_l1_set_max) {
                for my $j (0..$ram_l1_line_max) {
                    my $ci = $i + $j * ($ram_l1_set_max + 1);
                    print "                if      (cpu.cache.ram_l1_${ci}_addr == lin) { ret.r = cpu.cache.ram_l1_${ci}_val; }\n";
                    print "                else if (cpu.cache.ram_l1_${ci}_addr == lin + (1 << 2)) { ret.g = cpu.cache.ram_l1_${ci}_val; }\n";
                    print "                else if (cpu.cache.ram_l1_${ci}_addr == lin + (2 << 2)) { ret.b = cpu.cache.ram_l1_${ci}_val; }\n";
                    print "                else if (cpu.cache.ram_l1_${ci}_addr == lin + (3 << 2)) { ret.a = cpu.cache.ram_l1_${ci}_val; }\n";
                }
            }
?>

                    if (cpu.cache.ram_l1_last_addr == lin           ) { ret.r = cpu.cache.ram_l1_last_val; }
                else if (cpu.cache.ram_l1_last_addr == lin + (1 << 2)) { ret.g = cpu.cache.ram_l1_last_val; }
                else if (cpu.cache.ram_l1_last_addr == lin + (2 << 2)) { ret.b = cpu.cache.ram_l1_last_val; }
                else if (cpu.cache.ram_l1_last_addr == lin + (3 << 2)) { ret.a = cpu.cache.ram_l1_last_val; }
            }
        }
    }

    return ret;
}
#endif

#endif

/*

C# layout:

    #region LOAD
    private const int UART_BUFFER_SIZE = <?= $uart_buffer_max + 1 ?>;
    private int[] addr_lin(int lin) {
        int[] ret = new int[3];
        ret[2] = lin & 0x3; // c
        lin = lin >> 2;
        ret[0] = lin % <?= $width ?>; // x
        ret[1] = lin / <?= $width ?>; // y
        return ret;
    }
<?
for my $prop (sort { $state->{$a}->{addr} <=> $state->{$b}->{addr} } keys %$state) {
    my $n = $state->{$prop}->{name};
    my $a = $addr_lin->($state->{$prop}->{addr});
    my $t = $state->{$prop}->{type};

    if (!defined($state->{$prop}->{def})) {
        my $fname = $prop;
        next if $prop =~ m/uart_buffer\.buf/;
        $fname =~ s/\./__/;
        print "    private uint load_$fname() { return decodePackedData($a->{x}, $a->{y}, $a->{c}); }\n";
    }
}
?>    private uint load_csr(int addr) {
        int lin = (addr >> 2) + <?= $csr_cache_start ?>;
        return decodePackedData(lin % <?= $width ?>, lin / <?= $height ?>, addr & 0x3);
    }
    private uint getUartBuffer(int idx) {
        <?
        my $uart_start = $state->{"uart_buffer.buf0"}->{addr};
        my $uart_a = $addr_lin->($uart_start);
        ?>
        int lin = idx + <?= $uart_start ?>;
        int[] acc = addr_lin(lin);
        return decodePackedData(acc[0], acc[1], acc[2]);
    }
    #endregion

*/
