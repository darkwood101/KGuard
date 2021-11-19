#include <linux/kernel.h>
#include <linux/signal.h>
#include <linux/sched.h>
#include <linux/sched/signal.h>

asmlinkage long sys_kguard(void) {
    struct task_struct* t;
    struct pid* p;

    printk("Called kguard\n");
    t = get_current();
    p = get_task_pid(t, PIDTYPE_PID);
    kill_pid(p, SIGKILL, 1);
    return 0;
}

