#include <unistd.h>
#include <sys/syscall.h>
#include <stdio.h>

#define KGUARD_ENTRY    333
#define KGUARD_EXIT     334

int main() {
    syscall(333, 0x7fffaaaa);
    syscall(333, 0x7bcdebcd);
    syscall(333, 0xbde34567);
    syscall(334, 0xbde34567);
    syscall(334, 0x7bcdebcd);
    syscall(334, 0x7fffaaba);
}
