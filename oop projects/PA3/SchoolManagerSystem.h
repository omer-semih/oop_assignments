#ifndef SCHOOLMANAGEMENTSYSTEM_H
#define SCHOOLMANAGEMENTSYSTEM_H
#include<iostream>
#include<string>
#include "Student.h"
#include "Course.h"
using namespace std;

namespace PA3 {
class SchoolManagementSystem {

    private :
    Student** allStudents; // references of all student objects

    Course** allCourses; // references of all course objects

    public :
    SchoolManagementSystem(); // default constructor

    ~SchoolManagementSystem(); // destructor of school managament system

    Student** getAllStudents(); // getter function to access all students references

    Course** getAllCourses(); // getter function to access all courses references

    void menu_func(); // function that shows menu

    void student_menu(); // sub menu for student managament

    void select_student_menu(); // sub menu for selected student

    void course_menu(); // sub menu for course managament

    void select_course_menu(); // sub menu for selected course 

    void add_student(); // function that adds a new student

    int isAvailable(int size,int element); // function checks all students references dynamic array if it's full or not

    void list_all_students(); // function lists all students with name and ID

    void delete_student(string s_name,long int s_ID); // function that deletes student from program

    void add_selected_student_to_a_course(string name, long int ID,int index); // function that adds student to a course

    void drop_selected_student_from_a_course(string name, long int ID,int index); // function deletes student from a course

    void add_course(); // function adds a new course

    void list_all_courses(); // function lists all courses with code and name

    void delete_course(string code,string name); // function deletes course from program

    void list_students_registered_to_the_selected_course(string code,string name,int index); // function lists all taker students of a course

    // variables to store current number of element and size of dynamic student and course arrays
    int currentStudentSize, currentStudentElement, currentCourseSize, currentCourseElement; 
    
};
}
#endif