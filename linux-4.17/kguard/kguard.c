#include <linux/kernel.h>
#include <linux/syscalls.h>
#include <linux/signal.h>
#include <linux/sched.h>
#include <linux/sched/signal.h>

static void murder(struct task_struct* t);

SYSCALL_DEFINE1(kguard_entry, unsigned long, addr)
{
    struct task_struct* t = get_current();

    if  (!t->kguard_stack) {
        printk("KGuard ERROR: Entry: Null stack\n");
        goto error;
    }
    if (t->kguard_stack_sz == 1024) {
        printk("KGuard ERROR: Entry: Stack overflow\n");
        goto error;
    }

    printk("KGuard OK: Entry: Stored address 0x%px\n", (void*) addr);
    t->kguard_stack[t->kguard_stack_sz++] = addr;

    return 0;

error:
    murder(t);
    return -1;
}

SYSCALL_DEFINE1(kguard_exit, unsigned long, addr)
{
    struct task_struct* t = get_current();
    unsigned long stored_addr;

    if (!t->kguard_stack) {
        printk("KGuard ERROR: Return: Null stack\n");
        goto error;
    }
    if (t->kguard_stack_sz == 0) {
        printk("KGuard ERROR: Return: Empty stack\n");
        goto error;
    }

    stored_addr = t->kguard_stack[--t->kguard_stack_sz];
    if (stored_addr != addr) {
        printk("KGuard ERROR: Return: Address mismatch: "
               "KGuard remembers 0x%px, user popped 0x%px\n",
               (void*) stored_addr, (void*)  addr);
        goto error;
    }
    printk("KGuard OK: Return: Popped address 0x%px\n", (void*) addr);

    return 0;

error:
    murder(t);
    return -1;
}

void murder(struct task_struct* t)
{
    struct pid* p = get_task_pid(t, PIDTYPE_PID);
    kill_pid(p, SIGKILL, 1);
}

