#include <stdio.h>

// Function that computes factorial iteratively (loop, not recursion)
long long factorial(int n) {
  long long result = 1;
  for (int i = 1; i <= n; i++) {
    result *= i;
  }
  return result;
}

int main(void) {
  int n;

  // Asking user for n
  printf("Enter a non-negative integer (n): ");
  if (scanf("%d", &n) != 1) {
    printf("Error: Invalid input.\n");
    return 1;
  }

  // Controlling n < 0
  if (n < 0) {
    printf("Error: Factorial is not defined for negative numbers.\n");
  } else {
    // Calls the function and writes the result
    long long result = factorial(n);
    printf("%d! = %lld\n", n, result);
  }

  return 0;
}