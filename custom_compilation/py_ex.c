#include <stdio.h>

int fact(int n) {
    int res = 1;
    for (int i = 1; i <= n; i++) {
        res *= i;
    }
    return res;
}

int main() {
    int fact_5 = fact(5);
    printf("factorial of 5 is %d\n", fact_5);
    return 0;
}
