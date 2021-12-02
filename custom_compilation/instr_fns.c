#include <stdio.h>
#include <stdint.h>
#include <unistd.h>

#define KGUARD_ENTRY    333
#define KGUARD_EXIT     334

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
