/*
 * ...
 */


asmlinkage long sys_old_mmap(struct mmap_arg_struct __user *arg);

/* kguard/ */
asmlinkage long sys_kguard_entry(unsigned long addr);
asmlinkage long sys_kguard_exit(unsigned long addr);
asmlinkage long sys_kguard_setjmp(void* env);
asmlinkage long sys_kguard_longjmp(void* env);

/*
 * Not a real system call, but a placeholder for syscalls which are
 * not implemented -- see kernel/sys_ni.c
 */
asmlinkage long sys_ni_syscall(void);

/*
 * ...
 */

