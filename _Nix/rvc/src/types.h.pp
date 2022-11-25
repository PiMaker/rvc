#ifndef TYPES_H
#define TYPES_H

#define glsl_mod(x,y) (((x)-(y)*floor((x)/(y)))) 

<?:include header.p ?>

#define STALL_EXIT_CALL 1
#define STALL_CSR_CACHE 2
#define STALL_MEM_CACHE_L1 3
#define STALL_RESERVED 4
#define STALL_ILLEGAL_ENTRY_POINT 5
#define STALL_UART 6
#define STALL_FENCE 7
#define STALL_MEMOP_COPY 8

<?

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
my $s_arr = sub {
    my ($type, $name, $size) = @_;
    for my $i (0..($size - 1)) {
        my $nn = "${name}[${i}]";
        $state->{$nn} = {
            name => $nn,
            type => $type,
            addr => $addr,
        };
        $addr++;
    }
    if ($name =~ m/.*\.(.*)$/) {
        print "$type $1";
    } else {
        print "$type $name";
    }
    print "[${size}];";
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
    <? $s->("uint", "mmu.mode"); ?>
    <? $s->("uint", "mmu.ppn"); ?>
} mmu_state;

typedef struct {
    <? $s->("uint", "uart_buffer.ptr", 0xffffffff); ?>
    <?
    for my $i (0..$uart_buffer_max) {
        $s->("uint", "uart_buffer.buf${i}", 0);
        print "\n    ";
    }
    ?>
} uart_buffer;

typedef struct {
    <? $s->("uint", "stall"); ?>
    <? $s->("uint", "clock"); ?>
    <? $s->("uint", "commits"); ?>
    <? $s_arr->("uint", "xreg", 32); ?>
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

    <? $s->("uint", "rtc0"); ?>
    <? $s->("uint", "rtc1"); ?>

    <? $s->("float", "start_time_ref"); ?>

    <? $s->("uint", "debug_do_tick"); ?>
    <? $s->("uint", "debug_last_ins"); ?>
    <? $s->("uint", "debug_last_stall"); ?>
    <? $d->("uint", "debug_csr_val"); ?>
    <? $d->("uint", "debug_mem_val"); ?>

    <? $s->("uint", "debug_arb_0"); ?>
    /* <? $d->("uint", "debug_arb_1"); ?> */
    /* <? $d->("uint", "debug_arb_2"); ?> */
    /* <? $d->("uint", "debug_arb_3"); ?> */
    /* <? $d->("uint", "debug_arb_4"); ?> */
    /* <? $d->("uint", "debug_arb_5"); ?> */
    /* <? $d->("uint", "debug_arb_6"); ?> */
    /* <? $d->("uint", "debug_arb_7"); ?> */

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

#ifdef PASS_TICK
static uint4 l1_cache[<?= $ram_l1_size ?>];
#endif

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
    return cpu.xreg[i];
}

// ENCODE/DECODE LOGIC (state serialization into self texture)

<?

my $addr_lin = sub {
    my ($lin) = @_;
    my $col = $lin & 0x3;
    $lin = ($lin & (~0x3)) >> 2;
    return {
        x => $lin % $width_hart,
        y => int($lin / $width_hart),
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

# misnomer: csr_cache here is actually CSR data area, cache is in cpu_t
my $csr_cache_start = (($addr / 4) + 3) & (~0x3);
print "// csr_cache_start = $csr_cache_start (addr=$addr)\n";
my $l1_cache_start = $csr_cache_start + (4096/4);
my $l1_cache_end = $l1_cache_start + $ram_l1_size;
print "// l1_cache_start = $l1_cache_start (addr=$addr)\n";
print "// l1_cache_end = $l1_cache_end (addr=$addr)\n";

my $max_allowed = $width_hart * $height_hart;
die "too much data! max $max_allowed vs cur $l1_cache_end\n"
    if $l1_cache_end >= $max_allowed;

?>

#define STATE_WIDTH <?= $width_state ?>
#define STATE_HEIGHT <?= $height_state ?>

#ifdef PASS_TICK
void decode() {
    cpu = (cpu_t)0;

<?
    for my $prop (sort { $state->{$a}->{addr} <=> $state->{$b}->{addr} } keys %$state) {
        my $n = $state->{$prop}->{name};
        my $a = $addr_lin->($state->{$prop}->{addr});
        my $t = $state->{$prop}->{type};

        $t = "asfloat" if $t eq "float";

        if (defined($state->{$prop}->{def})) {
            print "    cpu.$n = $t($state->{$prop}->{def});\n";
        } else {
            print "    cpu.$n = $t(idx_uint4(STATE_TEX(uint2($a->{x}, $a->{y})), $a->{c}));\n";
        }
    }
?>
}
#endif

#ifdef PASS_COMMIT
#define NEEDS_DFC
#endif
#ifdef PASS_FB
#define NEEDS_DFC
#endif

#ifdef NEEDS_DFC
void decode_for_commit() {
    cpu = (cpu_t)0;

<?
    for my $prop (sort { $state->{$a}->{addr} <=> $state->{$b}->{addr} } keys %$state) {
        my $n = $state->{$prop}->{name};
        my $a = $addr_lin->($state->{$prop}->{addr});
        my $t = $state->{$prop}->{type};

        $t = "asfloat" if $t eq "float";

        # for committing only the L1 RAM and CSR caches are important
        # (not anymore?)
        # next if !($prop =~ m/cache\.ram/ || $prop =~ m/cache\.csr/);

        print "    cpu.$n = $t(idx_uint4(STATE_TEX_HART(uint2($a->{x}, $a->{y}), 0), $a->{c}));\n";
    }
?>
}
#endif

#ifdef PASS_TICK
bool pixel_has_state(uint2 pos) {
    // CSR data area and FB are not "state", they're only touched by commit
    uint lin = pos.x + <?= $width_hart ?> * pos.y;
    return lin < <?= $csr_cache_start ?> || (lin >= <?= $l1_cache_start ?> && lin < <?= $l1_cache_end ?>);
}

uint4 encode(uint2 pos) {
    // L1 cache
    uint s_lin = pos.x + pos.y * <?= $width_hart ?>;
    if (s_lin >= <?= $l1_cache_start ?> && s_lin < <?= $l1_cache_end ?>) {
        uint offset = s_lin - <?= $l1_cache_start ?>;
        return l1_cache[offset];
    }

    // fallback is passthrough
    uint4 ret = STATE_TEX(pos);

    // cpu_t serialization
    uint pos_id = pos.x | (pos.y << 16);
    [forcecase]
    switch (pos_id) {
<?
    for my $aid (sort keys %$rev) {
        print "    case $aid:\n";
        for my $prop (sort keys %{$rev->{$aid}}) {
            my $p = $rev->{$aid}->{$prop};
            my $c = $addr_lin->($p->{addr})->{c};
            $c = ("r", "g", "b", "a")[$c];
            my $conv = "uint";
            $conv = "asuint" if $p->{type} eq "float";
            if ($prop eq "debug_last_stall") {
                print "        ret.$c = $conv(cpu.stall == 0 ? cpu.debug_last_stall : cpu.stall);\n";
            } else {
                print "        ret.$c = $conv(cpu.$p->{name});\n";
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
    return idx_uint4(STATE_TEX(uint2(lin % <?= $width_hart ?>, lin / <?= $height_hart ?>)), idx);
}
#endif

uint mem_get_cached_or_tex_from_state_cache(uint addr) {
    // array-style L1 (direct texture access)
    for (uint i = 0; i < 2; i++) {
        uint arr_idx = RAM_L1_ARRAY_IDX(addr) + i * <?= $ram_l1_size / 2 ?>;
        uint lin = <?= $l1_cache_start ?> + arr_idx;
        uint4 cur = STATE_TEX_HART(uint2(lin % <?= $width_hart ?>, lin / <?= $height_hart ?>), 0);
             if (cur.x == addr) return cur.y;
        else if (cur.z == addr) return cur.w;
    }

    // query RAM texture
    uint idx = (addr >> 2) & 0x3;
    addr >>= 4;
    uint4 raw = STATE_TEX_HART(RAM_ADDR(addr), 0);
    return idx_uint4(raw, idx);
}

#ifdef PASS_COMMIT
uint mem_get_cached_or_tex_from_state_cache_or_mtd(uint addr) {
    if (addr & 0x80000000) {
        return mem_get_cached_or_tex_from_state_cache(addr & 0x7fffffff);
    } else if (addr & 0x40000000) {
        // query MTD/ROM
        uint mtd_addr = addr - 0x40000000;
        uint mtd_idx = (mtd_addr >> 2) & 0x3;
        mtd_addr = mtd_addr >> 4;
        uint2 mtd_lin = uint2(mtd_addr % m_dim.x, mtd_addr / m_dim.x);
        mtd_lin.y = m_dim.y - mtd_lin.y - 1;
        //[branch] if (mtd_lin.y >= m_dim.y) return 0;
        float4 full;
        [branch]
        switch (mtd_idx) {
            case 0:
                full = _Data_MTD_R[mtd_lin];
                break;
            case 1:
                full = _Data_MTD_G[mtd_lin];
                break;
            case 2:
                full = _Data_MTD_B[mtd_lin];
                break;
            case 3:
                full = _Data_MTD_A[mtd_lin];
                break;
        }
        return unpack_raw_float4(full);
    }
    return 0;
}

uint4 commit(uint2 pos) {
    if (pos.y < <?= $height_state ?> && pos.x >= <?= $width_state ?>) {
        return (uint4)0;
    }

    // fallback is passthrough
    uint4 ret = STATE_TEX_HART(pos, 0);

    uint pos_id = pos.x | ((pos.y) << 16);

    // increment commits
    if (!_Init && pos_id == <?= $addr_id->($state->{commits}->{addr}) ?>) {
        ++ret.<? my $c = $addr_lin->($state->{commits}->{addr})->{c}; $c = ("r", "g", "b", "a")[$c]; print $c; ?>;
    }

    // clear stalls
    if (pos_id == <?= $addr_id->($state->{stall}->{addr}) ?>) {
        switch (ret.<? my $c2 = $addr_lin->($state->{stall}->{addr})->{c}; $c2 = ("r", "g", "b", "a")[$c2]; print $c2; ?>) {
            case STALL_CSR_CACHE:
                ret.<?= $c2 ?> = 0;
                break;
            case STALL_MEM_CACHE_L1:
                ret.<?= $c2 ?> = 0;
                break;
            case STALL_FENCE:
                ret.<?= $c2 ?> = 0;
                break;
            case STALL_MEMOP_COPY: // will be handled now, so we can unset
                ret.<?= $c2 ?> = 0;
                break;
            case STALL_UART:
                ret.<?= $c2 ?> = 0;
                break;
        }
    }

    uint s_lin = pos.x + pos.y * <?= $width_hart ?>;

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
    if (pos.y >= <?= $height_state ?>) {
        uint2 pos_ram = uint2(pos.x, pos.y - <?= $height_state ?>);
        uint lin = pos_ram.x + pos_ram.y * <?= $total_width ?>;

        if (_Init) {
            // init main memory from texture
            uint2 ram_dim;
            _Data_RAM_A.GetDimensions(ram_dim.x, ram_dim.y);
            uint2 pos2 = uint2(pos.x, pos.y - <?= $height_state ?>);
            // something feels off here... off by one, you might say...
            // ...but this way it actually works
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
                        uint offset = lin_word - cpu.memop_dst_p;
                        uint src = cpu.memop_src_p + offset;
                        uint transfer = mem_get_cached_or_tex_from_state_cache_or_mtd(src);
                        set_idx_uint4(ret, transfer, icp);
                    }
                }
            } else {
                // write back L1 cache
                [loop]
                for (uint offset = 0; offset < 4; offset++) {
                    uint addr_off = lin + (offset << 2);
                    for (uint slice = 0; slice < 2; slice++) {
                        uint cache_idx = RAM_L1_ARRAY_IDX(addr_off) + slice * <?= $ram_l1_size / 2 ?>;
                        uint lin = <?= $l1_cache_start ?> + cache_idx;
                        uint4 cur = STATE_TEX_HART(uint2(lin % <?= $width_hart ?>, lin / <?= $height_hart ?>), 0);
                             if (cur.x == addr_off) { set_idx_uint4(ret, cur.y, offset); }
                        else if (cur.z == addr_off) { set_idx_uint4(ret, cur.w, offset); }
                    }
                }

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
    private const int STATE_WIDTH = <?= $width_state ?>;
    private const int STATE_HEIGHT = <?= $height_state ?>;
    private const int TOTAL_WIDTH = <?= $total_width ?>;
    private const int TOTAL_HEIGHT = <?= $total_height ?>;
    private int[] addr_lin(int lin) {
        int[] ret = new int[3];
        ret[2] = lin & 0x3; // c
        lin = lin >> 2;
        ret[0] = lin % <?= $width_hart ?>; // x
        ret[1] = lin / <?= $width_hart ?>; // y
        return ret;
    }
<?
for my $prop (sort { $state->{$a}->{addr} <=> $state->{$b}->{addr} } keys %$state) {
    my $n = $state->{$prop}->{name};
    my $a = $addr_lin->($state->{$prop}->{addr});
    my $t = $state->{$prop}->{type};

    if (!defined($state->{$prop}->{def})) {
        my $fname = $prop;
        $fname =~ s/\./__/;
        $fname =~ s/\]//;
        $fname =~ s/\[//;
        print "    private uint load_$fname() { return decodePackedData($a->{x}, $a->{y}, $a->{c}); }\n";
    }
}
?>    private uint load_csr(int addr) {
        int lin = (addr >> 2) + <?= $csr_cache_start ?>;
        return decodePackedData(lin % <?= $width_hart ?>, lin / <?= $height_hart ?>, addr & 0x3);
    }
    private uint load_l1_cache(int addr) {
        int lin = (addr >> 2) + <?= $l1_cache_start ?>;
        return decodePackedData(lin % <?= $width_hart ?>, lin / <?= $height_hart ?>, addr & 0x3);
    }
    #endregion

*/
