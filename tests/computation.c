#include <unistd.h>
#include <sys/syscall.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_PRIME 100000

// reference - https://stackoverflow.com/questions/9244481/how-to-get-100-cpu-usage-from-a-c-program
unsigned long do_primes(int r)
{
    unsigned long i, num, primes = 0;
    for (num = 1; num <= MAX_PRIME - r; ++num) {
        for (i = 2; (i <= num) && (num % i != 0); ++i);
        if (i == num)
            ++primes;
    }
    return primes;
}

// recursive definition forces stack to grow quickly, stress testing KGuard
int factorial(int i) {
  if (i == 1) return 1;
    else return i * factorial(i - 1);
}

int main() {
  int sum = 0;
    for (int i = 0; i < 10000; i++) {
        int r = rand();
        sum += factorial(r);
	sum += do_primes(r);
    }

    
    return sum - 10;
}

