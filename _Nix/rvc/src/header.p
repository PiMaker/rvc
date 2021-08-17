<?
my $csr_cache_max = 15;
my $uart_buffer_max = 63;
my $ram_l1_set_max = 15; # sets
my $ram_l1_line_max = 4; # words per line
?>

/* must match set/line count above, shift by two to ignore byte offset */
#define RAM_L1_TAG(a) ((a >> 2) & 0xf)
