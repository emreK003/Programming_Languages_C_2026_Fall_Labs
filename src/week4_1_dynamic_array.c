#include <stdio.h>
#include <stdlib.h>

int main(void) {
  int n;

  /* Asks the user for the number of elements */
  printf("Enter number of elements: ");
  if (scanf("%d", &n) != 1 || n <= 0) {
    printf("\nInvalid size.\n");
    return 1;
  }

  /* Dynamically allocates memory for an integer array using sizeof(int) */
  int* arr = malloc(n * sizeof(int));
  if (arr == NULL) {
    printf("\nMemory allocation failed.\n");
    return 1;
  }

  printf("Enter %d integers: ", n);
  long long sum = 0;
  for (int i = 0; i < n; i++) {
    if (scanf("%d", &arr[i]) != 1) {
      printf("\nInvalid input.\n");
      free(arr);
      return 1;
    }
    sum += arr[i];
  }

  double average = (double)sum / n;

  printf("Sum = %lld\n", sum);
  printf("Average = %.2f\n", average);

  free(arr);
  return 0;
}
