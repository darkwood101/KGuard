void __noreturn do_exit(long code)
{
	struct task_struct *tsk = current;
	int group_dead;

    if (tsk->kguard_stack || tsk->kguard_jbuf) {
        kfree(tsk->kguard_stack);
        printk("KGuard OK: Freed a stack at address %p\n",
                tsk->kguard_stack);
        kfree(tsk->kguard_jbuf);
        printk("KGuard OK: Freed setjmp/longjmp buffers at address %p\n",
                tsk->kguard_jbuf);
    }
	profile_task_exit(tsk);
	kcov_task_exit(tsk);

    /*
     * ... rest of do_exit
     */
}

