#include <unistd.h>
#include <sys/syscall.h>
#include <stdio.h>
#include <stdlib.h>
#include <wait.h>
#include <assert.h>

// recursive definition forces stack to grow quickly, stress testing KGuard                                                                                                                                 
int factorial(int i) {
  if (i == 1) return 1;
    else return i * factorial(i - 1);
}

int rand_factorial() {
  int r = rand();
  int sum = 0;
  for (int i = 0; i < r; i++) {
    int input = rand();
    sum += input;
  }
  return sum;
}


int main() {
  int counter = 0;
  while (counter < 10) {
    
    pid_t f = fork();
    if (f == 0) {
      int r = rand_factorial();
      exit(12);
    }
    counter++;
    int	status;
    wait(&status);
    assert(WIFEXITED(status));
  }
  
  return 0;
}



