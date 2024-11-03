#ifndef STUDENT_H
#define STUDENT_H
#include<iostream>
#include<string>
using namespace std;

namespace PA3 {
class Course;

class Student {

    private : 
    string name; // name of student

    long int ID; // school ID number of student

    Course** taken_courses; // course references that are taken by the student
    
    public :
    Student(); // default constructor

    Student(string name, long int ID); // constructor that creates an object with name and ID

    ~Student(); // destructor of student class

    string getName(); // getter func to get name

    Course** getCourses(); // getter func to get courses

    long int getID(); // getter func to get ID

    void setCourses(Course **ptr); // function that sets the pointer that points course references

    int currentTakenCourseSize, currentTakenCourseElement; // variables to store current number of elements and size of taken courses
    
};
}
#endif