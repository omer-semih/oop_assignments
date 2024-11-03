#include "SchoolManagerSystem.h"
#include<iostream>
#include<string>

namespace PA3 {
Student** SchoolManagementSystem::getAllStudents() { // getter function to access all students references
        return allStudents;
}

Course** SchoolManagementSystem::getAllCourses() { // getter function to access all courses references
        return allCourses;
}

SchoolManagementSystem::SchoolManagementSystem() { // default constructor

    // Initializing size's to 1 and number of elements to 0
    currentStudentSize = 1; 
    currentStudentElement = 0;
    currentCourseSize = 1;
    currentCourseElement = 0;

    // create size of 1 dynamic memory for the initialization
    allStudents = new Student*[1];
    allCourses = new Course*[1];
}

SchoolManagementSystem::~SchoolManagementSystem() { // Destructor for SchoolManagementSystem

    for(int i=0;i<currentStudentElement;i++) { // Deallocating memory of every single student's courses
        delete[] allStudents[i]->getCourses();
    }

    for(int i=0;i<currentCourseElement;i++) { // Deallocating memory of every single course's students
        delete[] allCourses[i]->getStudents();
    }

    delete[] allStudents; // deallocate all student references array
    delete[] allCourses; // deallocate all course references array

}

int SchoolManagementSystem::isAvailable(int size,int element) { // Function to check if space is available

    if(element == size-1) return 0;
    else return 1;

}

void SchoolManagementSystem::menu_func() {

string user_input;

    do {
        
        cout << "Main_menu" << endl; // print main menu and read input till user enters 0 to exit
        cout << "0 exit" << endl;
        cout << "1 student" << endl;
        cout << "2 course" << endl;
        cout << "3 list_all_students" << endl;
        cout << "4 list_all_courses" << endl << ">> ";

        cin >> user_input;

        if (user_input.length() != 1 || (user_input[0] < '0' || user_input[0] > '4')) {
            continue;  // check if the input is valid by checking elements of string input. if not , read again
        }

        char user_choice = user_input[0]; // set string's first character to choice if it's valid

        switch(user_choice) {
            case '0':
                break;

            case '1':
                student_menu(); // print student sub menu
                break;

            case '2':
                course_menu(); // print course sub menu
                break;

            case '3':
                list_all_students(); // print all students
                break;
                
            case '4':
                list_all_courses(); // print all courses
                break;
        }

    } while(user_input != "0"); // read input until user enters 0 to exit the program
}

void SchoolManagementSystem::student_menu() { 

    string user_input;

    do {
        cout << "0 up" << endl;
        cout << "1 add_student" << endl;
        cout << "2 select_student" << endl << ">> ";

        cin >> user_input;

        if (user_input.length() != 1 || (user_input[0] < '0' || user_input[0] > '2')) {
            continue; // check if the input is valid by checking elements of string input. if not , read again
        }

        char user_choice = user_input[0]; // set string's first character to choice if it's valid

        switch(user_choice) {
            case '0':   // if the input is zero , go to previous menu
                return;
                break;

            case '1':
                add_student(); // call student adding function
                break;

            case '2':
                select_student_menu(); // call function to select menu
                break;
        }

    } while(user_input != "0"); // read input until user enters 0 to go to the previous menu
}

void SchoolManagementSystem::select_student_menu() { 

    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // celan buffer
    string Name, id;
    bool found=false;
    long int ID;
    int j;

    while(!found) { // check if the entered student is found in program

    string line,name;
    getline(cin, line); // read line 
    
    int i = 0;
    while (line[i] < '0' || line[i] > '9') { // read until it sees a number that means id started
        name.push_back(line[i]);
        i++;
    }
    
    name.erase(name.size()-1); // delete last whitespace
    id = line.substr(i,name.size()-i);
    ID = stol(id); // convert string id to integer id 

    for(j=0;j<currentStudentElement;j++) { // check if the student is found
        if(allStudents[j]->getName() == name && allStudents[j]->getID() == ID) {
            found = true;
            break;
        }
    }
    Name = name;
    
    }

    string user_input; // string to store input

    do {
        cout << "0 up" << endl;           // print menu
        cout << "1 delete_student" << endl;
        cout << "2 add_selected_student_to_a_course" << endl;
        cout << "3 drop_selected_student_from_a_course" << endl << ">> ";

        cin >> user_input;

        if (user_input.length() != 1 || (user_input[0] < '0' || user_input[0] > '3')) {
            continue; // check if the input is valid
        }

        char user_choice = user_input[0]; // if the input is valid , get the input from string

        switch(user_choice) {
            case '0':   // go back to previous menu
                return;
                break;

            case '1':
                delete_student(Name,ID); // delete student from the program
                return;
                break;

            case '2':
                add_selected_student_to_a_course(Name,ID,j); // add student to course. j represents index
                break;

            case '3':
                drop_selected_student_from_a_course(Name,ID,j); // delete student from a course. j represents index
                break;
        }

    } while(user_input != "0"); // read input until user enters 0 to go to the previous menu
}

void SchoolManagementSystem::course_menu() {

    string user_input;

    do {
        cout << "0 up" << endl;
        cout << "1 add_course" << endl;
        cout << "2 select_course" << endl << ">> ";

        cin >> user_input;

        if (user_input.length() != 1 || (user_input[0] < '0' || user_input[0] > '2')) {
            continue; // check if the input is valid by checking elements of string input. if not , read again
        }

        char user_choice = user_input[0]; // set string's first character to choice if it's valid

        switch(user_choice) {
            case '0':   // go back to previous menu
                return;
                break;

            case '1':
                add_course(); // add new course to the program
                break;

            case '2':
                select_course_menu(); // select course to manage with other operations 
                break;
        }

    } while(user_input != "0"); // read input until user enters 0 to go to the previous menu

}

void SchoolManagementSystem::select_course_menu() {

    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // celan buffer
    string line, Code, Name;
    bool found=false;
    int j;

    while(!found) { // read course code and name until user enters valid ones

    string line,name,code;
    getline(cin, line);
    
    int i = 0;
    while (line[i] != ' ') { // when it sees a whitespace it means code finished and name has started
        code.push_back(line[i]);
        i++;
    }
    
    name = line.substr(i+1,line.size()-i-1); // create sub string for name of the course


    for(j=0;j<currentCourseElement;j++) {
        if(allCourses[j]->getCode() == code && allCourses[j]->getName() == name) {
            found = true; // check if the entered course code and name found
            break;
        }
    }

    Code = code;
    Name = name;
    }


    string user_input; // string variable to store input 

    do {
        cout << "0 up" << endl;
        cout << "1 delete_course" << endl;
        cout << "2 list_students_registered_to_the_selected_course" << endl << ">> ";

        cin >> user_input;

        if (user_input.length() != 1 || (user_input[0] < '0' || user_input[0] > '2')) {
            continue; // check if the input is valid by checking elements of string input. if not , read again
        }

        char user_choice = user_input[0]; // set string's first character to choice if it's valid

        switch(user_choice) {
            case '0':   // go back to previous menu
                return;
                break;

            case '1':
                delete_course(Code,Name); // delete course from program
                return;
                break;

            case '2':
                list_students_registered_to_the_selected_course(Code,Name,j); // list all students who are taking the selected course
                break; // parameter j represents index of the course
        }

    } while(user_input != "0"); // read input until user enters 0 to go to the previous menu
}

void SchoolManagementSystem::add_student() {

    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // celan buffer
    
    string line, name, id;
    long int ID;

    getline(cin, line); // get line 

    int i = 0;
    while (line[i] < '0' || line[i] > '9') { // Extracting name from input line
        name.push_back(line[i]);
        i++;
    }
    
    name.erase(name.size()-1); // delete last whitespace
    
    id = line.substr(i,line.size()-i); // Extracting ID from input line
    ID = stol(id);

    // Checking if there's enough space for the new student, if not, resize the array
    if( !isAvailable(currentStudentSize, currentStudentElement) ) {
        currentStudentSize += 10;

        Student **temp = new Student*[currentStudentSize];

        for(int i=0;i<currentStudentSize-10;i++) { // temp to store elements
            temp[i] = allStudents[i];
        }
    
        delete[] allStudents; // delete stored array of references
    
        allStudents = temp; // replace old array with new one 
    }

    allStudents[currentStudentElement] = new Student(name,ID); // create new student object dynamically
    currentStudentElement++; // increment number of students by one

}

void SchoolManagementSystem::delete_student(string s_name,long int s_ID) {

    for(int i=0;i<currentStudentElement;i++) { // Travelling through all students
     // Checking if the current student matches the provided name and ID
    if(allStudents[i]->getName() == s_name && allStudents[i]->getID() == s_ID) {
    // Looping through all courses taken by the current student
    for(int n=0;n<allStudents[i]->currentTakenCourseElement;n++) {    
    // Looping through all students in the current course
    for(int k=0;k<allStudents[i]->getCourses()[n]->currentTakerStudentElement;k++) {
    // Checking if the student is taking in the current course
    if(allStudents[i]->getCourses()[n]->getStudents()[k]->getName() == s_name && allStudents[i]->getCourses()[n]->getStudents()[k]->getID() == s_ID ) {
    // Shifting students' positions in the course array
    for(int m=k;m<allStudents[i]->getCourses()[n]->currentTakerStudentElement-1;m++) {
    allStudents[i]->getCourses()[n]->getStudents()[m] = allStudents[i]->getCourses()[n]->getStudents()[m+1];
    }
    // Setting the last index in the course array to NULL
    allStudents[i]->getCourses()[n]->getStudents()[allStudents[i]->getCourses()[n]->currentTakerStudentElement-1] = NULL;
    allStudents[i]->getCourses()[n]->currentTakerStudentElement -= 1; // Decreasing the count of students in the course
    break;
    } 
    }    
    }

    delete allStudents[i]; // Deleting the student object
    allStudents[i] = NULL;

    // Shifting students' positions in the student array
    for(int j=i;j<currentStudentElement-1;j++) {
    allStudents[j] = allStudents[j+1];
    }
    // Setting the last index of the student array to NULL
    allStudents[currentStudentElement-1] = NULL;
    currentStudentElement-=1; // Decreasing the count of students
    break;
    }
    }
}


void SchoolManagementSystem::delete_course(string code,string name) {

    // Traveling through all courses
    for(int i=0;i<currentCourseElement;i++) {
    // Checking if the current course matches the provided code and name
    if(allCourses[i]->getCode() == code && allCourses[i]->getName() == name) {
    // Traveling through all students taking the current course
    for(int n=0;n<allCourses[i]->currentTakerStudentElement;n++) {
    // Looping through all courses taken by the current student
    for(int k=0;k<allCourses[i]->getStudents()[n]->currentTakenCourseElement;k++) {
    // Checking if the course is taken by the current student    
    if(allCourses[i]->getStudents()[n]->getCourses()[k]->getCode() == code && allCourses[i]->getStudents()[n]->getCourses()[k]->getName() == name ) {
    // Shifting courses' positions in the student's course array
    for(int m=k;m<allCourses[i]->getStudents()[n]->currentTakenCourseElement-1;m++) {
    allCourses[i]->getStudents()[n]->getCourses()[m] = allCourses[i]->getStudents()[n]->getCourses()[m+1];
    }
    // Setting the last position in the student's course array to NULL
    allCourses[i]->getStudents()[n]->getCourses()[allCourses[i]->getStudents()[n]->currentTakenCourseElement-1] = NULL;
    allCourses[i]->getStudents()[n]->currentTakenCourseElement -= 1; // Decreasing the count of courses taken by the student
    break;
    }
    }
    }

    delete allCourses[i]; // Delete the course object
    allCourses[i] = NULL; // Setting the last index of the course array to NULL
    // Shifting courses' positions in the course array
    for(int j=i;j<currentCourseElement-1;j++) {
    allCourses[j] = allCourses[j+1];
    }
    // Setting the last position in the course array to NULL
    allCourses[currentCourseElement] = NULL;
    currentCourseElement-=1; // Decreasing the count of courses
    break;
    }
    }
}

void SchoolManagementSystem::list_all_students() { // print all students in the program

    for(int i=0;i<currentStudentElement;i++) { // looping through all students references array
        cout << allStudents[i]->getName() << " " << allStudents[i]->getID() << endl;
    }
}

void SchoolManagementSystem::list_all_courses() { // print all courses in the program

    for(int i=0;i<currentCourseElement;i++) { // looping through all course references array
        cout << allCourses[i]->getCode() << " " << allCourses[i]->getName() << endl;
    }
}

void SchoolManagementSystem::add_course() {

    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // celan buffer
    
    string line, code, name;
    long int ID;

    getline(cin, line);

    int i = 0;  // Extracting course code from input line
    while (line[i] != ' ') {
        code.push_back(line[i]);
        i++;
    }
    
    name = line.substr(i+1,line.size()-i-1); // Extracting course name from input line
    
    // Checking if there's enough space for the new course, if not, resize the array
    if( !isAvailable(currentCourseSize, currentCourseElement) ) {
        currentCourseSize += 10;

        Course **temp = new Course*[currentCourseSize]; // Creating a temporary array with increased size

        for(int i=0;i<currentCourseSize-10;i++) { // Copying existing elements to the temporary array
            temp[i] = allCourses[i];
        }
    
        delete[] allCourses; // Deallocating memory for the old array
    
        allCourses = temp; // Assigning the address of the new array to the old array pointer
    }

    allCourses[currentCourseElement] = new Course(code,name); // Creating a new Course object and adding it to the array
    currentCourseElement++; // increase total number of courses by one

}

void SchoolManagementSystem::add_selected_student_to_a_course(string name, long int ID,int index) {

int user_choice;
int counter = 1;
int *arr = new int[currentCourseElement];

// Displaying available courses for the selected student
cout << "0 up" << endl;
for(int i=0;i<currentCourseElement;i++) {
bool found = false;

    // Checking if the student is already enrolled in the course
    for(int j=0;j<allStudents[index]->currentTakenCourseElement;j++) {
        if(allStudents[index]->getCourses()[j] == allCourses[i] ) {
            found = true;
            break;
        }
    }
    // Adding courses not already taken by the student to the array and displaying them
    if(!found) {
    arr[counter-1] = i;
    cout << counter << " " << allCourses[i]->getCode() << " " << allCourses[i]->getName() << endl;
    counter++;
    }
}

 // Asking user to choose a course
cout << ">> ";
cin >> user_choice;
if(user_choice <= 0 || user_choice > counter-1) return; // check if the input is valid or 0

user_choice = arr[user_choice-1]; // Adjusting user_choice based on array index
delete[] arr; // delete array to store indexes of courses that are not taken by the student

// Checking if there's enough space for the new course in the student's list, if not, resize the array
if( !isAvailable(allStudents[index]->currentTakenCourseSize, allStudents[index]->currentTakenCourseElement) ) {
        allStudents[index]->currentTakenCourseSize += 10;

        Course **temp = new Course*[allStudents[index]->currentTakenCourseSize]; // Creating a temporary array with increased size

        for(int i=0;i<allStudents[index]->currentTakenCourseSize-10;i++) {
            temp[i] = allStudents[index]->getCourses()[i]; // Copying existing elements to the temporary array
        }
    
        delete[] allStudents[index]->getCourses(); // Deallocating memory for the old array
    
        allStudents[index]->setCourses(temp); // Assigning the address of the new array to the old array pointer
    }

    // Adding the selected course to the student's list of courses
    allStudents[index]->getCourses()[allStudents[index]->currentTakenCourseElement] = allCourses[user_choice];
    allStudents[index]->currentTakenCourseElement++;

    // Checking if there's enough space for the student in the course's list, if not, resize the array
   if( !isAvailable(allCourses[user_choice]->currentTakerStudentSize, allCourses[user_choice]->currentTakerStudentElement) ) {
        allCourses[user_choice]->currentTakerStudentSize += 10; // increase the size

        Student **temp = new Student*[allCourses[user_choice]->currentTakerStudentSize]; // Creating a temporary array with increased size

        for(int i=0;i<allCourses[user_choice]->currentTakerStudentSize-10;i++) {
            temp[i] = allCourses[user_choice]->getStudents()[i]; // Copying existing elements to the temporary array
        }
    
        delete[] allCourses[user_choice]->getStudents(); // Deallocating memory for the old array
    
        allCourses[user_choice]->setStudents(temp); // Assigning the address of the new array to the old array pointer
    }

    // Adding the selected student to the course's list of students
    allCourses[user_choice]->getStudents()[allCourses[user_choice]->currentTakerStudentElement] = allStudents[index];
    allCourses[user_choice]->currentTakerStudentElement++;

}

void SchoolManagementSystem::list_students_registered_to_the_selected_course(string code,string name,int index) {

    // Looping through all students registered for the selected course
    for(int i=0;i<allCourses[index]->currentTakerStudentElement;i++) {
        // Printing each student's name and ID
        cout << allCourses[index]->getStudents()[i]->getName() << " " << allCourses[index]->getStudents()[i]->getID() << endl;
    }
}

void SchoolManagementSystem::drop_selected_student_from_a_course(string name, long int ID,int index) {

    int user_choice;
    int counter = 1;
    int *arr = new int[currentCourseElement];

    cout << "0 up" << endl; // Displaying courses taken by the selected student
    for(int i=0;i<currentCourseElement;i++) {
    bool found = false;

    for(int j=0;j<allStudents[index]->currentTakenCourseElement;j++) { // Checking if the student is enrolled in the course
        if(allStudents[index]->getCourses()[j] == allCourses[i] ) {
            found = true;
            break;
        }
    }
    // Adding courses taken by the student to the array and displaying them
    if(found) {
    arr[counter-1] = i;
    cout << counter << " " << allCourses[i]->getCode() << " " << allCourses[i]->getName() << endl;
    counter++;
    }
    }

    cout << ">> "; // Asking user to choose a course to drop
    cin >> user_choice;
    if(user_choice <= 0 || user_choice > counter-1) return; // check if the input is valid

    user_choice = arr[user_choice-1]+1; // Adjusting user_choice based on array index
    delete[] arr; // deallocate array to store indexes of courses taken by the student

    int i,j;
    // Finding and dropping the student from the course's list of students
    for(i=0;i<allCourses[user_choice-1]->currentTakerStudentElement;i++) {
        // Checking if the current student matches the name and ID of the selected student
        if(allCourses[user_choice-1]->getStudents()[i]->getName() == name && allCourses[user_choice-1]->getStudents()[i]->getID() == ID) {
            // Shifting students' positions in the course's list of students
            for(j=i;j<allCourses[user_choice-1]->currentTakerStudentElement;j++) {
                allCourses[user_choice-1]->getStudents()[j] = allCourses[user_choice-1]->getStudents()[j+1];
            }
            // Setting the last position in the course's list of students to NULL
            allCourses[user_choice-1]->getStudents()[allCourses[user_choice-1]->currentTakerStudentElement-1] = NULL;
            allCourses[user_choice-1]->currentTakerStudentElement-=1; // Decreasing the number of students in the course by one
            break;
        }
    }

    // Finding and dropping the selected course from the student's list of courses
    for(i=0;i<allStudents[index]->currentTakenCourseElement;i++) {
        // Checking if the current course matches the code and name of the selected course
        if(allStudents[index]->getCourses()[i]->getCode() == allCourses[user_choice-1]->getCode() && allStudents[index]->getCourses()[i]->getName() == allCourses[user_choice-1]->getName() ){
            // Shifting courses' positions in the student's list of courses
            for(j=i;j<allStudents[index]->currentTakenCourseElement;j++) {
                allStudents[index]->getCourses()[j] = allStudents[index]->getCourses()[j+1];
            }
            // Setting the last position in the student's list of courses to NULL
            allStudents[index]->getCourses()[allStudents[index]->currentTakenCourseElement-1] = NULL;
            allStudents[index]->currentTakenCourseElement-=1; // Decreasing the count of courses taken by the student by one
            break;
        }
    }

}
}