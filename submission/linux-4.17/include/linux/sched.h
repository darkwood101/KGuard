struct task_struct {
#ifdef CONFIG_THREAD_INFO_IN_TASK
	/*
	 * For reasons of header soup (see current_thread_info()), this
	 * must be the first element of task_struct.
	 */
	struct thread_info		thread_info;
#endif
	/* -1 unrunnable, 0 runnable, >0 stopped: */
	volatile long			state;

	/*
	 * This begins the randomizable portion of task_struct. Only
	 * scheduling-critical items should be added above here.
	 */
	randomized_struct_fields_start
    unsigned long           *kguard_stack;
    unsigned long           kguard_stack_sz;
    struct kguard_jmp_buf   *kguard_jbuf;
    unsigned long           kguard_num_bufs;

	void				*stack;
	atomic_t			usage;

	/*
	 * ... rest of task_struct
	 */
}
