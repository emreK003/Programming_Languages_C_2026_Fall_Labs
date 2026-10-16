/*
 * Week 5 - Task 1: Read and Write Data from Files
 *
 * Name:       Emre
 * Surname:    Kiyak
 * Student ID: 260AEM008
 *
 * Writes a few lines of text into a file with fprintf(), closes it,
 * then reopens it and prints its contents line by line using fgets().
 * Optional: the file name can be given as the first command-line argument.
 */

#include <stdio.h>

#define DEFAULT_FILENAME "data.txt"
#define LINE_SIZE 256

int main(int argc, char* argv[]) {
  /* Use the file name from the command line if given, else the default */
  const char* filename = (argc > 1) ? argv[1] : DEFAULT_FILENAME;
  char line[LINE_SIZE];
  int lines_read = 0;

  /* ---- Step 1-3: open for writing, write lines, close ---- */
  FILE* fp = fopen(filename, "w");
  if (fp == NULL) {
    perror("Error opening file for writing");
    return 1;
  }

  printf("Writing lines to %s...\n", filename);
  fprintf(fp, "Hello, file I/O in C!\n");
  fprintf(fp, "This is another line.\n");
  fclose(fp);

  /* ---- Step 4-5: open for reading, print every line ---- */
  fp = fopen(filename, "r");
  if (fp == NULL) {
    perror("Error opening file for reading");
    return 1;
  }

  printf("Reading contents:\n");
  while (fgets(line, sizeof(line), fp) != NULL) {
    printf("%s", line);
    lines_read++;
  }
  fclose(fp);

  /* Bonus: report how many lines were read */
  printf("Lines read: %d\n", lines_read);

  return 0;
}
