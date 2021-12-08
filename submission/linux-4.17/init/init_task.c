/*
 * Set up the first task table, touch at your own risk!. Base=0,
 * limit=0x1fffff (=2MB)
 */
struct task_struct init_task
#ifdef CONFIG_ARCH_TASK_STRUCT_ON_STACK
	__init_task_data
#endif
= {
#ifdef CONFIG_THREAD_INFO_IN_TASK
	.thread_info	= INIT_THREAD_INFO(init_task),
	.stack_refcount	= ATOMIC_INIT(1),
#endif
	.state		= 0,
    .kguard_stack = NULL,
    .kguard_stack_sz = 0,
    .kguard_jbuf = NULL,
    .kguard_num_bufs = 0,
	.stack		= init_stack,
	.usage		= ATOMIC_INIT(2),
	.flags		= PF_KTHREAD,

    /*
     *  ... rest of init_task
     */

}
