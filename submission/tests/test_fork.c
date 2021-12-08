#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void foo(void) {
    pid_t p = fork();
    if (p == 0) {
        printf("Hello from the child!\n");
        return;
    }
    int wstatus;
    wait(&wstatus);
    assert(WIFEXITED(wstatus));
}

int main(void) {
    foo();
}
