#include <stdio.h>

// the function that compute the sum of integers 1 through n with for loop
int sum_to_n(int n) {
  int sum = 0;
  for (int i = 1; i <= n; i++) {
    sum += i;
  }
  return sum;
}

int main(void) {
  int n;

  // taking input value for n from the user
  printf("Enter a positive integer (n): ");
  if (scanf("%d", &n) != 1) {
    printf("Error: Invalid input.\n");
    return 1;
  }

  // controlling n < 1
  if (n < 1) {
    printf("Error: n must be greater than or equal to 1.\n");
  } else {
    // calls the function and prints the result
    int result = sum_to_n(n);
    printf("The sum from 1 to %d is: %d\n", n, result);
  }

  return 0;
}