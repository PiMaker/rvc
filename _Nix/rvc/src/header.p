<?
my $width_state = 64;
my $height_state = 64;
my $width_hart = 64;
my $height_hart = 64;
my $total_width = 2048;
my $total_height = 4096;

my $csr_cache_max = 15;
my $uart_buffer_max = 63;
my $ram_l1_size = 1024;
?>

<?
print "#define RAM_ADDR(lin) uint2(lin % $total_width, $height_state + (lin / $total_width))\n";
print "#define RAM_MAX ($total_width * ($total_height - $height_state) * 4 * 4)\n";
?>

/* shift by two to ignore byte offset */
#define RAM_L1_ARRAY_IDX(a) (((a >> 2) & <?= $ram_l1_size/8 - 1 ?>) | (((a >> <?= log($ram_l1_size/2)/log(2) + 2 ?>) & 0x3) << <?= log($ram_l1_size/2)/log(2) - 2 ?>))
