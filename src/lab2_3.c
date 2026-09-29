#include <stdio.h>

// function that returns 1 if prime, 0 if not.
int is_prime(int n) {
  if (n < 2) {
    return 0;
  }
  for (int i = 2; i * i <= n; i++) {
    if (n % i == 0) {
      return 0;  // prime
    }
  }
  return 1;  // not prime
}

int main(void) {
  int n;

  // asking user for n
  printf("Enter an integer n (n >= 2): ");
  if (scanf("%d", &n) != 1) {
    printf("Error: Invalid input.\n");
    return 1;
  }

  // asking user for n
  if (n < 2) {
    printf("Error: n must be greater than or equal to 2.\n");
  } else {
    printf("Prime numbers up to %d:\n", n);
    // controlling the integers 2 through n and printing the primes
    for (int i = 2; i <= n; i++) {
      if (is_prime(i)) {
        printf("%d ", i);
      }
    }
    printf("\n");
  }

  return 0;
}