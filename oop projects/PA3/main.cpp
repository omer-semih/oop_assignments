#include<iostream>
#include<string> // include necessary libraries
#include "SchoolManagerSystem.h"
using namespace std;
using namespace PA3;

int main() {

    SchoolManagementSystem* m1 = new SchoolManagementSystem; // create dynamically created schoolmanagamentsystem object
    m1->menu_func(); // call main menu function
    delete m1; // deallocate dynamically allocated everything through SchoolManagamentSystem destructor

    return 0;
}