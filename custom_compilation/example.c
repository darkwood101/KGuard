#include <stdio.h>

int fact(int n) {
    int res = 1;
    for (int i = 1; i <= n; i++) {
        res *= i;
    }
    return res;
}

void safe_fn() {
    printf("entered safe function (not protected by kguard)\n");
}

int main() {
    int fact_5 = fact(5);
    printf("factorial of 5 is %d\n", fact_5);
    safe_fn();
    return 0;
}
