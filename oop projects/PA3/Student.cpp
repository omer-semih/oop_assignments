#include "Student.h"
#include "Course.h"
#include<iostream>
#include<string>

namespace PA3 {
Student::Student() { // Default constructor for the Student class
    taken_courses = new Course*[1]; // Allocating memory with initial value of 1
    currentTakenCourseSize = 1; // Setting the initial size of the array
    currentTakenCourseElement = 0; // Setting the current element index to 0
}

Student::Student(string name, long int ID) { // Parameterized constructor for the Student class

    taken_courses = new Course*[1]; // Allocating memory with initial value of 1
    currentTakenCourseSize = 1; //  initialize the current size with 1
    currentTakenCourseElement = 0; // initialize the current element index with 0
    this->name = name; // Assign name 
    this->ID = ID; // Assign ID 
}

Student::~Student() {
    if( taken_courses != NULL) {
        delete[] taken_courses; // delete dynamic memory if pointer is not null
    }
}

string Student::getName() { // getter func to get name
    return name;
}

long int Student::getID() { // getter func to get ID
    return ID;
}

Course** Student::getCourses() { // getter func to get courses
    return taken_courses;
}

void Student::setCourses(Course **ptr) { // function that sets the pointer that points course references
    taken_courses = ptr;
}
}