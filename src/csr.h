#ifndef CSR_H
#define CSR_H

#include "types.h"

uint get_csr(uint addr) {
    // TODO
    printf("CSR read: %x\n", addr);
    return 0;
}

void set_csr(uint addr, uint val) {
    // TODO
    printf("CSR write: %x <- %x\n", addr, val);
}

#endif
