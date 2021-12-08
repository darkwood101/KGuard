/*
 *  Ok, this is the main fork-routine.
 *
 * It copies the process, and if successful kick-starts
 * it and waits for it to finish using the VM if required.
 */
long _do_fork(unsigned long clone_flags,
	      unsigned long stack_start,
	      unsigned long stack_size,
	      int __user *parent_tidptr,
	      int __user *child_tidptr,
	      unsigned long tls)
{
	struct completion vfork;
	struct pid *pid;
	struct task_struct *p;
	int trace = 0;
	long nr;

	/*
	 * Determine whether and which event to report to ptracer.  When
	 * called from kernel_thread or CLONE_UNTRACED is explicitly
	 * requested, no event is reported; otherwise, report if the event
	 * for the type of forking is enabled.
	 */
	if (!(clone_flags & CLONE_UNTRACED)) {
		if (clone_flags & CLONE_VFORK)
			trace = PTRACE_EVENT_VFORK;
		else if ((clone_flags & CSIGNAL) != SIGCHLD)
			trace = PTRACE_EVENT_CLONE;
		else
			trace = PTRACE_EVENT_FORK;

		if (likely(!ptrace_event_enabled(current, trace)))
			trace = 0;
	}

	p = copy_process(clone_flags, stack_start, stack_size,
			 child_tidptr, NULL, trace, tls, NUMA_NO_NODE);
	add_latent_entropy();
    
	if (IS_ERR(p))
		return PTR_ERR(p);

    if ((clone_flags & CLONE_KGUARD) || current->kguard_stack) {
        p->kguard_stack = kmalloc(1024 * sizeof(*p->kguard_stack), GFP_KERNEL);
        p->kguard_jbuf = kmalloc(16 * sizeof(*p->kguard_jbuf), GFP_KERNEL);
        if (p->kguard_stack && p->kguard_jbuf) {
            printk("KGuard OK: Allocated a stack at address %p\n",
                    p->kguard_stack);
            printk("KGuard OK: Allocated setjmp/longjmp buffers at address %p\n",
                    p->kguard_jbuf);
            p->kguard_stack_sz = 0;
            p->kguard_num_bufs = 0;
            if (current->kguard_stack) {
                memcpy(p->kguard_stack,
                       current->kguard_stack,
                       current->kguard_stack_sz * sizeof(*p->kguard_stack));
                p->kguard_stack_sz = current->kguard_stack_sz;
            }
        } else {
            printk("KGuard ERROR: Failed to allocate metadata\n");
            kfree(p->kguard_stack);
            kfree(p->kguard_jbuf);
        }
    } else {
        p->kguard_stack = NULL;
        p->kguard_jbuf = NULL;
    }

    /*
     * ... rest of _do_fork
     */
}
