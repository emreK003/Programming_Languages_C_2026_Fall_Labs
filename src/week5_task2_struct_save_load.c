/*
 * Week 5 - Task 2: Save and Load Structured Records
 *
 * Name:       Emre
 * Surname:    Kiyak
 * Student ID: 260AEM008
 *
 * Saves one Student record to a text file (format: "name age gpa")
 * and loads it back, then prints the loaded record.
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
 * Writes the student as one line "name age gpa" to the given file.
 * Returns 0 on success, -1 on failure.
 */
int save_student(const Student* s, const char* filename) {
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

/*
 * Reads one student record from the given file into *s.
 * Returns 0 on success, -1 if the file cannot be opened or
 * the data cannot be read completely.
 */
int load_student(const char* filename, Student* s) {
  FILE* fp = fopen(filename, "r");
  if (fp == NULL) {
    return -1;
  }

  /* %49s limits the name so it cannot overflow name[50] */
  int fields = fscanf(fp, "%49s %d %f", s->name, &s->age, &s->gpa);
  fclose(fp);

  if (fields != 3) {
    return -1;
  }
  return 0;
}

int main(void) {
  const char* filename = "student.txt";
  Student original = {"Alice", 21, 3.75f};
  Student loaded;

  memset(&loaded, 0, sizeof(loaded));

  printf("Saving student to file...\n");
  if (save_student(&original, filename) != 0) {
    fprintf(stderr, "Error: could not save student to %s\n", filename);
    return 1;
  }

  printf("Loading student from file...\n");
  if (load_student(filename, &loaded) != 0) {
    fprintf(stderr, "Error: could not load student from %s\n", filename);
    return 1;
  }

  printf("Loaded student: %s, %d, GPA %.2f\n", loaded.name, loaded.age,
         loaded.gpa);

  return 0;
}