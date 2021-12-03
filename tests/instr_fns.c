#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <setjmp.h>

#define KGUARD_ENTRY    333
#define KGUARD_EXIT     334
#define KGUARD_SETJMP   335
#define KGUARD_LONGJMP  336

void __cyg_profile_func_enter(void *this_fn, void *call_site) {
    uintptr_t* ret_addr_ptr = (uintptr_t*) call_site;
    printf("fn entry: ret addr %p\n", ret_addr_ptr);
    syscall(KGUARD_ENTRY, *ret_addr_ptr);
}

void __cyg_profile_func_exit(void *this_fn, void *call_site) {
    uintptr_t* ret_addr_ptr = (uintptr_t*) call_site;
    printf("fn exit: ret addr %p\n", ret_addr_ptr);
    syscall(KGUARD_EXIT, *ret_addr_ptr);
}

int setjmp_safe(jmp_buf buf) {
    int x = setjmp(buf);
    if (x == 0) {
        syscall(KGUARD_SETJMP, buf);
    }
    return x;
}

void longjmp_safe(jmp_buf buf, int val) {
    syscall(KGUARD_LONGJMP, buf);
    longjmp(buf, val);
}
