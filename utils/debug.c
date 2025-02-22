//
// Created by mtoia on 01/01/25.
//

#include "../include/ft_ls.h"

void print_5_bits(int num) {
    int mask = 0b11111; // Mask to extract the 5 least significant bits
    int bits = num & mask; // Extract the 5 bits

    for (int i = 4; i >= 0; i--) {
        int bit = (bits >> i) & 1; // Extract the i-th bit
        ft_printf("%d", bit);
    }
    ft_printf("\n");
}