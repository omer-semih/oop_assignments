#ifndef COURSE_H
#define COURSE_H
#include<iostream>
#include<string>
using namespace std;

namespace PA3 {
class Student;
class Course {

    private :
    string code, name; // code and name of course

    Student **taker_students; // student references who takes this course

    public :
    Course(); // default constructor

    Course(string code,string name); // constructor that creates an obejct with code and name 

    ~Course(); // destructor of Course class

    string getName(); // getter function to access name of the course

    string getCode(); // getter function to access code of the course

    Student** getStudents(); // getter function to access pointer that points to the references of taker students

    void setStudents(Student **ptr); // function that sets the pointer that points to taker students' references

    int currentTakerStudentSize, currentTakerStudentElement; // variables to store current number of elements and size of taker students

};
}
#endif