#ifndef _KGUARD_H_
#define _KGUARD_H_

struct jmp_buff {
    long long int       buf[8];
    int                 mask_was_saved;
    unsigned long int   padding[1024 / (8 * sizeof(unsigned long))];
};

struct kguard_jmp_buf {
    struct jmp_buff        buf;
    unsigned long          stack_entry;
    unsigned long          buf_addr;
};

#endif

