/*
 * Week 5 - Task 3: Student Management System with File Persistence
 *
 * Name:       Emre
 * Surname:    Kiyak
 * Student ID: 260AEM008
 *
 * Menu-driven program: list, add, and save students.
 * Data is stored in students.txt, one record per line: name,ID,GPA
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 100
#define NAME_SIZE 50
#define LINE_SIZE 256
#define FILENAME "students.txt"

typedef struct Student {
  char name[NAME_SIZE];
  int id;
  float gpa;
} Student;

/*
 * Safely reads one line from stdin into buf (without the newline).
 * Returns 1 on success, 0 on end of input.
 */
static int read_line(char* buf, size_t size) {
  if (fgets(buf, (int)size, stdin) == NULL) {
    return 0;
  }

  size_t len = strlen(buf);
  if (len > 0 && buf[len - 1] == '\n') {
    buf[len - 1] = '\0';
  } else if (len + 1 == size) {
    /* Line was longer than the buffer: discard the rest of it */
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
  }
  return 1;
}

/*
 * Loads students from students.txt into arr (at most max records).
 * Returns the number of students loaded; 0 if the file does not exist.
 * Blank or malformed lines are skipped.
 */
int load_students(Student arr[], int max) {
  FILE* fp = fopen(FILENAME, "r");
  if (fp == NULL) {
    /* First run: no file yet, not an error */
    return 0;
  }

  char line[LINE_SIZE];
  int count = 0;

  while (count < max && fgets(line, sizeof(line), fp) != NULL) {
    char name[NAME_SIZE];
    int id;
    float gpa;

    /* sscanf returns 3 only if all fields were parsed */
    if (sscanf(line, "%49[^,],%d,%f", name, &id, &gpa) != 3) {
      continue; /* blank or malformed line */
    }

    strcpy(arr[count].name, name);
    arr[count].id = id;
    arr[count].gpa = gpa;
    count++;
  }

  fclose(fp);
  return count;
}

/*
 * Overwrites students.txt with all current records.
 * Returns 0 on success, -1 on failure.
 */
int save_students(const Student arr[], int count) {
  FILE* fp = fopen(FILENAME, "w");
  if (fp == NULL) {
    return -1;
  }

  for (int i = 0; i < count; i++) {
    fprintf(fp, "%s,%d,%.2f\n", arr[i].name, arr[i].id, arr[i].gpa);
  }

  if (fclose(fp) != 0) {
    return -1;
  }
  return 0;
}

/*
 * Asks for name, ID and GPA, validates them and appends a new student.
 */
void add_student(Student arr[], int* count, int max) {
  char name[LINE_SIZE];
  char id_text[LINE_SIZE];
  char gpa_text[LINE_SIZE];
  char* end;

  if (*count >= max) {
    printf("Cannot add more students (limit reached).\n");
    return;
  }

  printf("Enter name: ");
  if (!read_line(name, sizeof(name))) {
    return;
  }
  printf("Enter ID: ");
  if (!read_line(id_text, sizeof(id_text))) {
    return;
  }
  printf("Enter GPA: ");
  if (!read_line(gpa_text, sizeof(gpa_text))) {
    return;
  }

  /* Name: not empty, no comma, fits into the array */
  if (name[0] == '\0' || strchr(name, ',') != NULL ||
      strlen(name) >= NAME_SIZE) {
    printf("Invalid input. Student not added.\n");
    return;
  }

  /* ID: must be a whole number */
  long id = strtol(id_text, &end, 10);
  if (end == id_text || *end != '\0' || id < 0 || id > 2147483647L) {
    printf("Invalid input. Student not added.\n");
    return;
  }

  /* GPA: must be a number between 0.0 and 4.0 */
  double gpa = strtod(gpa_text, &end);
  if (end == gpa_text || *end != '\0' || gpa < 0.0 || gpa > 4.0) {
    printf("Invalid input. Student not added.\n");
    return;
  }

  strcpy(arr[*count].name, name);
  arr[*count].id = (int)id;
  arr[*count].gpa = (float)gpa;
  (*count)++;

  printf("Student added successfully!\n");
}

/*
 * Prints one student per line: ID, name, GPA.
 */
void list_students(const Student arr[], int count) {
  if (count == 0) {
    printf("No students found.\n");
    return;
  }

  printf("%-6s%-20s%s\n", "ID", "Name", "GPA");
  for (int i = 0; i < count; i++) {
    printf("%-6d%-20s%.2f\n", arr[i].id, arr[i].name, arr[i].gpa);
  }
}

int main(void) {
  Student students[MAX_STUDENTS];
  int count = 0;
  char line[LINE_SIZE];

  count = load_students(students, MAX_STUDENTS);
  printf("Loaded %d student(s) from %s\n", count, FILENAME);

  for (;;) {
    printf("\n=== Student Management System ===\n");
    printf("1. List students\n");
    printf("2. Add student\n");
    printf("3. Save and Exit\n");
    printf("Select an option: ");

    /* End of input behaves like "Save and Exit" */
    if (!read_line(line, sizeof(line))) {
      printf("\n");
      break;
    }

    if (strcmp(line, "1") == 0) {
      list_students(students, count);
    } else if (strcmp(line, "2") == 0) {
      add_student(students, &count, MAX_STUDENTS);
    } else if (strcmp(line, "3") == 0) {
      break;
    } else {
      printf("Invalid option. Please try again.\n");
    }
  }

  if (save_students(students, count) != 0) {
    fprintf(stderr, "Error: could not save students to %s\n", FILENAME);
    return 1;
  }
  printf("Data saved. Goodbye!\n");

  return 0;
}