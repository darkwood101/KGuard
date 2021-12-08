#include <stdio.h>
#include <pthread.h>

void foo(void) {
    printf("Hello from foo\n");
}

void* run_thread(__attribute__((unused)) void* unused) {
    foo();
}

int main(void) {
    pthread_t t;
    pthread_create(&t, NULL, &run_thread, NULL);
    pthread_join(t, NULL);
}
