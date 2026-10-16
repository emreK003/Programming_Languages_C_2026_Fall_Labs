/*
 * Week 5 - Bonus Task 4: Binary File Version
 *
 * Name:       Emre
 * Surname:    Kiyak
 * Student ID: 260AEM008
 *
 * Saves a Student record in binary format (student.bin) with fwrite(),
 * loads it back with fread(), also saves it as text (student.txt) and
 * compares the sizes of both files.
 */

#include <stdio.h>
#include <string.h>

#define NAME_SIZE 50

typedef struct Student {
  char name[NAME_SIZE];
  int age;
  float gpa;
} Student;

/*
 * Writes the whole struct to a binary file.
 * Returns 0 on success, -1 on failure.
 */
int save_student_binary(const Student* s, const char* filename) {
  FILE* fp = fopen(filename, "wb");
  if (fp == NULL) {
    return -1;
  }

  /* fwrite returns the number of items written; it must be 1 */
  if (fwrite(s, sizeof(Student), 1, fp) != 1) {
    fclose(fp);
    return -1;
  }

  if (fclose(fp) != 0) {
    return -1;
  }
  return 0;
}

/*
 * Reads the whole struct from a binary file.
 * Returns 0 on success, -1 on failure.
 */
int load_student_binary(const char* filename, Student* s) {
  FILE* fp = fopen(filename, "rb");
  if (fp == NULL) {
    return -1;
  }

  /* fread returns the number of items read; it must be 1 */
  if (fread(s, sizeof(Student), 1, fp) != 1) {
    fclose(fp);
    return -1;
  }

  fclose(fp);
  return 0;
}

/*
 * Returns the size of a file in bytes (using fseek/ftell), or -1 on error.
 */
long file_size(const char* filename) {
  FILE* fp = fopen(filename, "rb");
  if (fp == NULL) {
    return -1;
  }

  if (fseek(fp, 0, SEEK_END) != 0) {
    fclose(fp);
    return -1;
  }

  long size = ftell(fp);
  fclose(fp);
  return size;
}

/* Saves the student as one text line "name age gpa" (same as Task 2). */
static int save_student_text(const Student* s, const char* filename) {
  FILE* fp = fopen(filename, "w");
  if (fp == NULL) {
    return -1;
  }

  if (fprintf(fp, "%s %d %.2f\n", s->name, s->age, s->gpa) < 0) {
    fclose(fp);
    return -1;
  }

  if (fclose(fp) != 0) {
    return -1;
  }
  return 0;
}

int main(void) {
  const char* bin_name = "student.bin";
  const char* txt_name = "student.txt";

  /* Zero-initialise so padding and unused name bytes are not garbage */
  Student original = {0};
  Student loaded = {0};

  strcpy(original.name, "Alice");
  original.age = 21;
  original.gpa = 3.75f;

  printf("Saving student in binary format...\n");
  if (save_student_binary(&original, bin_name) != 0) {
    fprintf(stderr, "Error: could not save %s\n", bin_name);
    return 1;
  }

  printf("Loading student from binary file...\n");
  if (load_student_binary(bin_name, &loaded) != 0) {
    fprintf(stderr, "Error: could not load %s\n", bin_name);
    return 1;
  }
  printf("Loaded student: %s, %d, GPA %.2f\n", loaded.name, loaded.age,
         loaded.gpa);

  /* Save the same record as text to compare file sizes */
  if (save_student_text(&original, txt_name) != 0) {
    fprintf(stderr, "Error: could not save %s\n", txt_name);
    return 1;
  }

  printf("Text file size: %ld bytes\n", file_size(txt_name));
  printf("Binary file size: %ld bytes\n", file_size(bin_name));

  return 0;
}