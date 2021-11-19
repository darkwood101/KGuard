#include <linux/kernel.h>

asmlinkage long sys_kguard(void) {
    printk("Called kguard\n");
    return 4536765;
}

