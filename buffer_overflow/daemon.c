#define _GNU_SOURCE
#include <sys/syscall.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define STACK_SZ 0x800000

int run_child(void* args);

int main(int argc, char** argv) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <program> [<args>]\n", argv[0]);
        return EXIT_SUCCESS;
    }

    char* stack_bottom = malloc(STACK_SZ);
    if (!stack_bottom) {
        fprintf(stderr, "%s:%d: Error in malloc: %s\n",
                __FILE__, __LINE__, strerror(errno));
        return EXIT_FAILURE;
    }

    pid_t pid = clone(&run_child, stack_bottom + STACK_SZ,
                      0x1000, argv + 1);
    if (pid < 0) {
        fprintf(stderr, "%s:%d: Error in clone: %s\n",
                __FILE__, __LINE__, strerror(errno));
        free(stack_bottom);
        return EXIT_FAILURE;
    }
    sleep(0.5);
    int wstatus;
    if (waitpid(pid, &wstatus, __WALL) < 0) {
        fprintf(stderr, "%s:%d: Error in waitpid: %s\n",
                __FILE__, __LINE__, strerror(errno));
        free(stack_bottom);
        return EXIT_FAILURE;
    }

    if (WIFEXITED(wstatus)) {
        fprintf(stdout, "Child exited with status %d\n", WEXITSTATUS(wstatus));
    } else if (WIFSIGNALED(wstatus)) {
        fprintf(stdout, "Child terminated by signal %d\n", WTERMSIG(wstatus));
    } else {
        fprintf(stdout, "Child terminated for unknown reasons\n");
    }

    free(stack_bottom);
    return EXIT_SUCCESS;
}

int run_child(void* args) {
    char** argv = (char**) args;
    execv(argv[0], argv);
    fprintf(stderr, "%s:%d: Error in execv: %s\n",
            __FILE__, __LINE__, strerror(errno));
}

