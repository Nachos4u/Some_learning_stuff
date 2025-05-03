#include "Student.h"
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

void* printStudent(void* args);
bool lesserStudent(Student*, Student*);

Student* createStudent(
    const char* firstName, const char* lastName, bool gender, int age,
     const char* group, int mathMark, int phisikMark, int chemMark){
    Student* student = (Student*)malloc(sizeof(Student));
    student->firstName = firstName;
    student->lastName = lastName;
    student->gender = gender;
    student->age = age;
    student->group = group;
    student->mathMark = mathMark;
    student->phisikMark = phisikMark;
    student->chemMark = chemMark;
    student->print = printStudent;
    student->lesser = lesserStudent;
    return student;
}

void* printStudent(void* args){
    Student* student = (Student*) args;
    if((!student->lastName) || (!student->firstName) || (!student->age) ||
     (!student->group) || (!student->mathMark) || (!student->phisikMark) || 
     (!student->chemMark) || ((student->gender != false) && (student->gender != true))){
        printf("ERROR, FAILER!");
        return (void*) 1;
    }
    printf("LastName: %s, firstName: %s, ", student->lastName, student->firstName);
    printf("gender: %s", student->gender ? "male, " : "female, ");
    printf("age: %d, group: %s, math: %d, phisik: %d, chem: %d\n", 
        student->age, student->group, student->mathMark, student->phisikMark, student->chemMark);
}

bool lesserStudent(Student* first, Student* second){
    if ((!first->mathMark) || (!second->mathMark)){
        return NULL; 
    }
    return first->mathMark < second->mathMark;
}
