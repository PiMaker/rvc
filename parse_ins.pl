#!/usr/bin/env perl

use warnings;
use strict;

my $file = 'instructions.txt';
open my $info, $file or die "Could not open $file: $!\n";

my $ins = {};
my $cur_ins;

while(my $line = <$info>) {
    $line =~ s/(^\s+|\s+$)//;
    if ($line =~ m/^Instruction/) {
	if ($cur_ins && $cur_ins->{name}) {
	    $ins->{delete $cur_ins->{name}} = $cur_ins;
	}
	$cur_ins = {};
    } elsif ($line =~ m/^mask: ([0-9abcdefx]+),/) {
	$cur_ins->{mask} = $1;
    } elsif ($line =~ m/^data: ([0-9abcdefx]+),/) {
	$cur_ins->{data} = $1;
    } elsif ($line =~ m/^name:\s*"(.+)",/) {
	my $n = lc $1;
	$n =~ s/\./_/g;
	$cur_ins->{name} = $n;
    } elsif ($line =~ m/^disassemble: dump_(.+),?$/) {
	my $f = $1;
	$f =~ s/_mem$//;
	$cur_ins->{format} = $f;
    }
}
$ins->{delete $cur_ins->{name}} = $cur_ins;

# add layers to the onion

my $ins_masks = {};
foreach my $name (keys %$ins) {
    my $mask = $ins->{$name}->{mask};
    $ins_masks->{$mask}->{$name} = $ins->{$name};
}

# parse opcode directory
sub parse_opcode_file {
    my ($file) = @_;
}

my $opcode_dir = {};
for my $fname (<riscv-opcodes/opcodes-*>) {
    $fname =~ m/\/opcodes-(.*)$/;
    my $dir = $1;

    open my $dirf, $fname or die "Could not open $fname: $!\n";

    while(my $line = <$dirf>) {
	next if $line =~ m/^\s*$/;
	next if $line =~ m/^@/;
	next if $line =~ m/^#/;

	$line =~ m/^(.+?)\s/;
	my $op = $1;
	$op =~ s/\./_/g;
	if (exists($opcode_dir->{$op})) {
	    die "instruction registered multiple times: $op\n";
	}
	$opcode_dir->{$op} = $dir;
    }

    close $dirf;
}

my $fmt = {
    format_r => "FormatR",
    format_r2 => "FormatR",
    format_i => "FormatI",
    format_s => "FormatS",
    format_u => "FormatU",
    format_j => "FormatJ",
    format_b => "FormatB",
    format_csr => "FormatCSR",
    empty => "FormatEmpty",
    unknown => "FormatEmpty /* UNKNOWN */",
};

my $l1 = 0;
my $l2 = 0;

my $supported = {
    rv32i => 1,
    rv32m => 1,
    rv32a => 1,
    system => 1,
};

my @accepted = ();

foreach my $name (sort keys %$ins) {
    # DEF(addi, FormatI, {
    $l2++;
    my $format = $fmt->{$ins->{$name}->{format} // "unknown"};
    die "unknown format: '$ins->{$name}->{format}'\n" if !$format;

    my $dir = $opcode_dir->{$name} or die "unknown instruction origin: $name\n";
    next if !exists($supported->{$dir});
    $l1++;

    print "DEF($name, $format, { // $dir\n    NOT_IMPL\n})\n";
}

print "\n";

foreach my $mask (sort keys %$ins_masks) {
    my $out = "";
    $out .= "ins_masked = ins_word & $mask;\n";
    $out .= "switch (ins_masked) {\n";
    my $found = 0;
    foreach my $name (sort keys %{$ins_masks->{$mask}}) {
	# RUN(addi, 0x00000013)
	my $dir = $opcode_dir->{$name} or die "unknown instruction origin: $name\n";
	next if !exists($supported->{$dir});

	my $format = $fmt->{$ins->{$name}->{format} // "unknown"};

	$out .= "    RUN($name, $ins->{$name}->{data}, ins_$format)\n";
	$found++;
    }

    next if !$found;

    $out .= "}\n";
    print $out;
}

print "\n";
print "Found $l2 instructions, accepted $l1\n";


close $info;
