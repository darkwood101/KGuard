#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/wait.h>

int setjmp_safe(jmp_buf buf);
void longjmp_safe(jmp_buf buf, int val);

jmp_buf buf1;
jmp_buf buf2;

void baz(int buf) {
    printf("Hello from baz\n");
    if (buf == 1)
        longjmp_safe(buf1, 1);
    else if (buf == 2)
        longjmp_safe(buf2, 1);
    else
        abort();    // should never reach here
}

void bar(int buf) {
    printf("Hello from bar\n");
    baz(buf);
}

void foo(int buf) {
    printf("Hello from foo\n");
    bar(buf);
}

void misbehave(void) {
    *((char*) buf1) = 0x57;
    longjmp_safe(buf1, 1);
    abort();    // should not reach here
}

int main(void) {
    if (setjmp_safe(buf1) == 0) {
        foo(1);
    }
    // Do it again!
    if (setjmp_safe(buf1) == 0) {
        foo(1);
    }
    // Again, but slightly different
    if (setjmp_safe(buf2) == 0) {
        foo(2);
    }
    printf("Great!\n");
    printf("Let's make sure the process will die if it misbehaves...\n");

    pid_t p = fork();
    if (p == 0) {
        if (setjmp_safe(buf1) == 0) {
            misbehave();
        } 
    } else {
        int wstatus;
        wait(&wstatus);
        assert(WIFSIGNALED(wstatus) && WTERMSIG(wstatus) == SIGKILL);
    }
    return 0;
}
