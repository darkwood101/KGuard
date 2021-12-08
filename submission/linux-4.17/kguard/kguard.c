#include <linux/kernel.h>
#include <linux/syscalls.h>
#include <linux/signal.h>
#include <linux/sched.h>
#include <linux/sched/signal.h>
#include <linux/uaccess.h>
#include <linux/string.h>
#include <kguard.h>

static void murder(struct task_struct* t);

struct jmp_buff checking_buf;

SYSCALL_DEFINE1(kguard_setjmp, void*, env)
{
    struct task_struct* t = get_current();
    struct kguard_jmp_buf* buf = NULL;
    unsigned long i;
    unsigned long not_copied;

    if (!t->kguard_jbuf) {
        printk("KGuard ERROR: setjmp: Null setjmp/longjmp buffer array\n");
        goto error;
    }

    for (i = 0; i != t->kguard_num_bufs; ++i) {
        if (t->kguard_jbuf[i].buf_addr == (unsigned long) env) {
            buf = &t->kguard_jbuf[i];
            break;
        }
    }

    if (!buf) {
        if (t->kguard_num_bufs == 16) {
            printk("KGuard ERROR: setjmp: Too many setjmp buffers\n");
            goto error;
        }
        buf = &t->kguard_jbuf[t->kguard_num_bufs++];
    }

    not_copied = copy_from_user(&buf->buf,
                                env,
                                sizeof(struct jmp_buff));
    if (not_copied != 0) {
        printk("KGuard ERROR: setjmp: Could not copy information from user space\n");
        goto error;
    }
    buf->stack_entry = t->kguard_stack_sz;
    buf->buf_addr = (unsigned long) env;

    printk("KGuard OK: setjmp: Remember to reset shadow stack to address 0x%px"
           "with jmp_buf at addres 0x%px\n",
           (t->kguard_stack_sz == 0) ? NULL : (void*) t->kguard_stack[t->kguard_stack_sz - 1],
           env);

    return 0;

error:
    murder(t);
    return -1;
}

SYSCALL_DEFINE1(kguard_longjmp, void*, env)
{
    struct task_struct* t = get_current();
    struct kguard_jmp_buf* buf = NULL;
    unsigned long i;
    unsigned long not_copied;

    if (!t->kguard_jbuf) {
        printk("KGuard ERROR: longjmp: Null setjmp/longjmp buffer array\n"); 
        goto error;
    }

    for (i = 0; i != t->kguard_num_bufs; ++i) {
        if (t->kguard_jbuf[i].buf_addr == (unsigned long) env) {
            buf = &t->kguard_jbuf[i];
            break;
        }
    }

    if (!buf) {
        printk("KGuard ERROR: longjmp: Buffer non-existent\n");
        goto error;
    }

    not_copied = copy_from_user(&checking_buf,
                                env,
                                sizeof(struct jmp_buff));
    if (not_copied != 0) {
        printk("KGuard ERROR: longjmp: Could not copy information from user space\n");
        goto error;
    }
    if (memcmp(&checking_buf, &buf->buf, sizeof(struct jmp_buff)) != 0) {
        printk("KGuard ERROR: longjmp: Buffer mismatch\n");
        goto error;
    }
    if (buf->stack_entry > t->kguard_stack_sz) {
        printk("KGuard ERROR: longjmp: setjmp caller already returned\n");
        goto error;
    }

    t->kguard_stack_sz = buf->stack_entry;

    printk("KGuard OK: longjmp: Reset shadow stack to address 0x%px"
           "with jmp_buf at addres 0x%px\n",
           (t->kguard_stack_sz == 0) ? NULL : (void*) t->kguard_stack[t->kguard_stack_sz - 1],
           env);

    return 0;

error:
    murder(t);
    return -1;
}

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

