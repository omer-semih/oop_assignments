#include "Student.h"
#include "Course.h"
#include<iostream>
#include<string>

namespace PA3 {

Course::Course() {  // Default constructor for the Course class
    taker_students = new Student*[1]; // Allocating memory with initial value of 1
    currentTakerStudentSize = 1; // initial size is 1 
    currentTakerStudentElement = 0; // initial number of taker students is 0
}

Course::Course(string code,string name) { // Parameterized constructor for the Course class
    taker_students = new Student*[1]; // Allocating memory with initial value of 1
    currentTakerStudentSize = 1; // initial size is 1 
    currentTakerStudentElement = 0; // initial number of taker students is 0
    this->code = code; // set code of course
    this->name = name; // set name of course
}

Course::~Course() {
    if(taker_students != NULL ) {
        delete[] taker_students; // delete dynamic memory if pointer is not null
    }
}

string Course::getName() { // getter function to access name of the course
    return name;
}

string Course::getCode() { // getter function to access code of the course
    return code;
}

Student** Course::getStudents() { // getter function to access pointer that points to the references of taker students
    return taker_students;
}

void Course::setStudents(Student **ptr) { // function that sets the pointer that points to taker students' references
    taker_students = ptr;
}
}