#ifndef UNIC_STUDENT
#define UNIC_STUDENT
#include <stdbool.h>

typedef struct Student{
    const char* firstName;
    const char* lastName;
    bool gender;
    int age;
    const char* group;
    int mathMark; int phisikMark; int chemMark;

    void* (*print)(void* args);
    bool (*lesser)(struct Student*, struct Student*);
}Student;

Student* createStudent(
    const char* firstName, const char* lastName, bool gender, int age,
     const char* group, int mathMark, int phisikMark, int chemMark);

#endif