#include<iostream>
#include<fstream>
#include <sstream>
#include<vector>
#include<string>
#include <algorithm>
using namespace std;

class field;

//-------------------------------------------------------------------------------------------------------------
class fieldFormat { // class that represents the pieces of field
public:
    string field_name;
    string field_type;
    bool is_array_or_not;
};

//-------------------------------------------------------------------------------------------------------------
class formatEntries {
public:
    vector <fieldFormat> allFormats; // class that represents the first line of file
};
//-------------------------------------------------------------------------------------------------------------
class field {
public:
    field() {}
    virtual bool search(const string& value) { return false; } // search in field
    virtual void printField(ofstream& o_file) {} // print field to file
    string getFieldData;
};
//-------------------------------------------------------------------------------------------------------------
class line_entry {
public:
    vector<field*> line_fields; // class represents line with vector fields
    void printLine(ofstream& o_file);
    bool searchLine(const string& value, int fieldIndex);
};

void line_entry::printLine(ofstream& o_file) { // prints the line to output.txt file
    for(int i=0;i<line_fields.size();i++) {
        line_fields[i]->printField(o_file);
        if(i != line_fields.size()-1)
        o_file << "|";
        }
        o_file << endl;
}

bool line_entry::searchLine(const string& value, int fieldIndex) { // searches in line
    if (fieldIndex >= 0 && fieldIndex < line_fields.size()) {
        return line_fields[fieldIndex]->search(value);
    }
    return false; 
}
//-------------------------------------------------------------------------------------------------------------
class subField_S_string : public field {
public:
    void printField(ofstream& o_file) override;  // class represents a field that contains single string
    string information;
    subField_S_string(string Data); // parameterized constructor
    bool search(const string& value) override;
};

subField_S_string::subField_S_string(string Data) { // constructor that assigns the data
    information = Data;
    getFieldData = Data;
}

void subField_S_string::printField(ofstream& o_file) {  // prints field
    o_file << information;
}

bool subField_S_string::search(const string& value) { // searches in field
    return information.find(value) != string::npos;
}

//-------------------------------------------------------------------------------------------------------------

class subField_M_string : public field {
public:
    vector<string> information;
    void printField(ofstream& o_file) override;  // class represents a field that contains multi string
    subField_M_string(string Data);
    bool search(const string& value) override;
};

void subField_M_string::printField(ofstream& o_file) { // prints field 
    for (int i = 0; i < information.size(); i++) {
        if(i != information.size()-1) o_file << information[i] << ":";
        else o_file << information[i];
    }
}

subField_M_string::subField_M_string(string Data) { // parameterized constructor that parses data
    stringstream ss(Data);
    string token;
    while (getline(ss, token, ':'))
        information.push_back(token);

    getFieldData = Data;
}

bool subField_M_string::search(const string& value) { // searches in string 
    for (const string& str : information) {
        if (str.find(value) != string::npos) {
            return true;
        }
    }
    return false;
}
//-------------------------------------------------------------------------------------------------------------
class subField_S_int : public field {
public:
    void printField(ofstream& o_file) override; // class represents a field that contains single integer
    int information;
    subField_S_int(string Data);
    bool search(const string& value) override;
};

void subField_S_int::printField(ofstream& o_file) { // prints field
    o_file << information;
}

subField_S_int::subField_S_int(string Data) { // parameterized constructor that conversts string to integer
    information = stoi(Data);
    getFieldData = Data;
}

bool subField_S_int::search(const string& value) { // searches in field
    // Convert value to int and compare
    try {
        int intValue = stoi(value);
        return information == intValue;
    } catch (const std::exception& e) {
        return false; // If value is not a valid integer
    }
}
//-------------------------------------------------------------------------------------------------------------
class subField_M_int : public field { // class represents a field that contains multi integer
public:
    vector<int> information;
    void printField(ofstream& o_file) override;
    subField_M_int(string Data);
    bool search(const string& value) override;
};

void subField_M_int::printField(ofstream& o_file) { // prints field to the file
    for (int i = 0; i < information.size(); i++) {
        o_file << information[i] << " ";
    }
}

subField_M_int::subField_M_int(string Data) { // parameterized constructor that parses data and conversts string to integer 
    int temp_int;
    stringstream ss(Data);
    string token;
    while (getline(ss, token, ':')) {
        temp_int = stoi(token);
        information.push_back(temp_int);
    }
    getFieldData = Data;
}

bool subField_M_int::search(const string& value) { // searches in field
    try {
    int intValue = stoi(value);
    for (int num : information) {
        if (num == intValue) {
            return true;
        }
    }
    return false; 
    } catch (const std::exception& e) {
    return false; 
    }
}
//-------------------------------------------------------------------------------------------------------------
class subField_S_double : public field {  // class represents a field that contains single double
public:
    void printField(ofstream& o_file) override; // prints field
    double information;
    subField_S_double(string Data);
    bool search(const string& value) override;
};

void subField_S_double::printField(ofstream& o_file)  { // prints field to file
    o_file << information;
}

subField_S_double::subField_S_double(string Data) { // parameterized consturctor that converts string to double
    information = stod(Data);
    getFieldData = Data; 
}

bool subField_S_double::search(const string& value)  { // searches in field
    try {
    double doubleValue = stod(value);
    return information == doubleValue;
    } catch (const std::exception& e) {
    return false;
    }
}
//-------------------------------------------------------------------------------------------------------------
class subField_M_double : public field { // class represents a field that contains multi doubles
public:
    vector<double> information;
    void printField(ofstream& o_file) override; // prints field to file
    subField_M_double(string Data);
    bool search(const string& value) override;
};

void subField_M_double::printField(ofstream& o_file) { // prints field to file
    for (int i = 0; i < information.size(); i++) {
        o_file << information[i] << " ";
    }
}

subField_M_double::subField_M_double(string Data) { // parameterized constructor that parses doubles and stores
    double temp_double;
    stringstream ss(Data);
    string token;
    while (getline(ss, token, ':')) {
        temp_double = stod(token);
        information.push_back(temp_double);
    }

    getFieldData = Data;
}

bool subField_M_double::search(const string& value) { // searches in field
    try {
    double doubleValue = stod(value);
    for (double num : information) {
        if (num == doubleValue) {
        return true;
        }
    }
    return false; 
    } catch (const std::exception& e) {
    return false;
    }
}
//-------------------------------------------------------------------------------------------------------------
class subField_S_char : public field { // class represents a field that contains single char
public:
    void printField(ofstream& o_file) override;
    char information;
    subField_S_char(string Data);
    bool search(const string& value) override;
};

void subField_S_char::printField(ofstream& o_file) { // prints field to an output file
    o_file << information;
}

subField_S_char::subField_S_char(string Data) { // parameterized constructor that assigns single char
    information = Data[0];
    getFieldData = Data;
}

bool subField_S_char::search(const string& value) { // searches in field
    if (value.length() == 1) {
        return information == value[0];
    }
    return false;
}
//-------------------------------------------------------------------------------------------------------------
class subField_M_char : public field { // class represents a field that contains multi char
public:
    vector<char> information;
    void printField(ofstream& o_file) override;
    subField_M_char(string Data);
    bool search(const string& value) override;
};

void subField_M_char::printField(ofstream& o_file) { // prints field to an output file
    for (int i = 0; i < information.size(); i++) {
        o_file << information[i] << " ";
    }
}

subField_M_char::subField_M_char(string Data) { // parses given data - parameterized constructor 
    stringstream ss(Data);
    string token;
    while (getline(ss, token, ':')) {
        information.push_back(token[0]);
    }
    getFieldData = Data;
}

bool subField_M_char::search(const string& value) { // searches in file
    for (char ch : information) {
        if (value.find(ch) != string::npos) {
            return true;
        }
    }
    return false;
}
//-------------------------------------------------------------------------------------------------------------
class inventory {
public:
    inventory() {};
    formatEntries data; // represents first line
    vector<line_entry> all_lines; // represents all lines
    void parse_first_line(string firstLine); // parses first line entries
    int searchInventory(const string& value, const string& fieldName, ofstream& outputFile); // searches in inventory
    int sortInventory(const string& fieldName, ofstream& outputFile); // sorts inventory
};

void inventory::parse_first_line(string firstLine) {
    stringstream ss(firstLine);
    string token;

    while (getline(ss, token, '|')) { // Split the line by '|'
        
        stringstream section(token); // stringstream to parse each section separated by ':'
        string first, second, third;

        // Split the section by ':'
        getline(section, first, ':');
        getline(section, second, ':');
        getline(section, third, ':');

        
        fieldFormat temp;  // Create a temporary class and fill it
        temp.field_name = first;
        temp.field_type = second;
        if (third == "multi") temp.is_array_or_not = true;
        else temp.is_array_or_not = false;

                                           
        data.allFormats.push_back(temp);  // Add the temporary class to the vector
    }

}

int inventory::searchInventory(const string& value, const string& fieldName, ofstream& outputFile) {
    int fieldIndex = -1;
    for (int i = 0; i < data.allFormats.size(); ++i) {
        if (data.allFormats[i].field_name == fieldName) {
            fieldIndex = i; // if found break
            break;
        }
    }

    if (fieldIndex == -1) { // If no matched field return -1 indicates error exception
        return -1;
    }

    for (line_entry& line : all_lines) {
        if (line.searchLine(value, fieldIndex)) { // searches in line and if found prints
            line.printLine(outputFile);
        }
    }

    return 1;
}

bool isInteger(const std::string& s) { // checks given data is integer or not
    return !s.empty() && std::all_of(s.begin(), s.end(), ::isdigit);
}

bool isDouble(const std::string& s) { // checks given data is double or not
    std::istringstream iss(s);
    double d;
    char c;
    return iss >> d && !(iss >> c);
}

int inventory::sortInventory(const string& fieldName, ofstream& outputFile) {
    int fieldIndex = -1;
    for (int i = 0; i < data.allFormats.size(); ++i) {
        if (data.allFormats[i].field_name == fieldName) {
            fieldIndex = i; // if found break
            break;
        }
    }

    if (fieldIndex == -1) {
        return -1; // If no matched field return -1 indicates error exception
    }


    sort(all_lines.begin(), all_lines.end(), 
         [&](const line_entry& a, const line_entry& b) {
             const std::string& a_data = a.line_fields[fieldIndex]->getFieldData;
             const std::string& b_data = b.line_fields[fieldIndex]->getFieldData;

             bool is_a_integer = isInteger(a_data);
             bool is_b_integer = isInteger(b_data); // check if given line is integers
             bool is_a_double = isDouble(a_data); // check if given line is doubles
             bool is_b_double = isDouble(b_data);

             if (is_a_integer && is_b_integer) { // if integers implement integer algorithm
                 int a_num = std::stoi(a_data);
                 int b_num = std::stoi(b_data);
                 return a_num < b_num;
             } else if (is_a_double && is_b_double) { // if doubles implement integer algorithm
                 double a_num = std::stod(a_data);
                 double b_num = std::stod(b_data);
                 return a_num < b_num;
             } else {
                 return a_data < b_data;
             }
         });

    for (line_entry& line : all_lines) {
        line.printLine(outputFile); // print sorted inventory lines
    }

    return 1;
}
//-------------------------------------------------------------------------------------------------------------

int main() {
    inventory Inventory;
    ifstream inputFile("data.txt"); // Open input file
    ifstream commandFile("commands.txt"); // Open command file
    ofstream outputFile("output.txt"); // Open output files

    if (!inputFile || !commandFile || !outputFile) {
        cout << "Error: Unable to open file." << endl;
        return 1; // If any of files couldn't be open , terminate program
    }

    string firstLine;
    getline(inputFile, firstLine);
    Inventory.parse_first_line(firstLine); // parse first line

    string tempLine;
    while (getline(inputFile, tempLine)) {
        
        stringstream ss(tempLine);
        string token;
        int counter = 0;
        line_entry currentLine;
        
        while (getline(ss, token, '|')) { // create fields depends on type

            if (Inventory.data.allFormats[counter].field_type == "string") { // string type fields 
                if (Inventory.data.allFormats[counter].is_array_or_not) { // multi case
                    subField_M_string *ptr = new subField_M_string(token);
                    currentLine.line_fields.push_back(ptr); // push to line
                }
                else {
                    subField_S_string *ptr = new subField_S_string(token); // single case
                    currentLine.line_fields.push_back(ptr); // push to line
                }
            }

            else if (Inventory.data.allFormats[counter].field_type == "integer") { // integer type fields
                if (Inventory.data.allFormats[counter].is_array_or_not) { // multi case
                    subField_M_int *ptr = new subField_M_int(token);
                    currentLine.line_fields.push_back(ptr); // push to line
                }
                else {
                    subField_S_int *ptr = new subField_S_int(token); // single case
                    currentLine.line_fields.push_back(ptr); // push to line
                }

            }

            else if (Inventory.data.allFormats[counter].field_type == "double") { // double type fields
                if (Inventory.data.allFormats[counter].is_array_or_not) { // multi case
                    subField_M_double *ptr = new subField_M_double(token);
                    currentLine.line_fields.push_back(ptr); // push to line
                }
                else {
                    subField_S_double *ptr = new subField_S_double(token); // single case
                    currentLine.line_fields.push_back(ptr); // push to line
                }

            }

            else if (Inventory.data.allFormats[counter].field_type == "char") { // char type fields
                if (Inventory.data.allFormats[counter].is_array_or_not) { // multi case
                    subField_M_char *ptr = new subField_M_char(token);
                    currentLine.line_fields.push_back(ptr); // push to line
                }
                else {
                    subField_S_char *ptr = new subField_S_char(token); // single case
                    currentLine.line_fields.push_back(ptr); // push to line
                }

            }

            counter++;
        }

        Inventory.all_lines.push_back(currentLine); // push the line to inventory
    }
    
    for(int i=0; i<Inventory.data.allFormats.size(); i++) { // print field names to output file
    outputFile << Inventory.data.allFormats[i].field_name;
        if(i != Inventory.data.allFormats.size()-1) {
            outputFile << "|";
        }
    }
    outputFile << endl;
    
    
    for(int i=0; i<Inventory.all_lines.size(); i++) { // check exceptions of fields
        try {
            if(Inventory.all_lines[i].line_fields.size() != Inventory.data.allFormats.size()) {
                throw runtime_error("Exception: missing field"); // check if there is a missing field
                
            } 
            else { 
                for(int j=i+1 ; j<Inventory.all_lines.size(); j++) {
                    try {
                    if(Inventory.all_lines[i].line_fields[0]->getFieldData == Inventory.all_lines[j].line_fields[0]->getFieldData) {
                        throw runtime_error("Exception: duplicate entry"); // check if entry is duplicated

                    }
                    }
                    catch(const runtime_error& e) { // catch error
                    outputFile << e.what() << endl;
                    Inventory.all_lines[j].printLine(outputFile);
                    Inventory.all_lines.erase(Inventory.all_lines.begin() + j);
                    }

                }
            }
            
        }
        catch(const runtime_error& e) { // catch missing field error
            
            outputFile << e.what() << endl;
            Inventory.all_lines[i].printLine(outputFile);
            Inventory.all_lines.erase(Inventory.all_lines.begin() + i);
        }

    }
    

    outputFile << Inventory.all_lines.size() << " unique entries" << endl; // print number of unique entries

    string commandLine;
    while (getline(commandFile, commandLine)) { // read commands file
        
        string command, value, fieldName;
        istringstream line(commandLine);
        line >> command; 

        if (command == "search") { // if the command is search catch "" and read datas
        
        size_t firstSen = commandLine.find('"'); // position of first "
        if (firstSen == string::npos) {
            continue;
        }

        size_t secondSen = commandLine.find('"', firstSen + 1); // position of second "
        if (secondSen == string::npos) {
            continue;
        }

        size_t thirdSen = commandLine.find('"', secondSen + 1); // position of third "
        if (thirdSen == string::npos) {
            continue;
        }

        size_t fourthSen = commandLine.find('"', thirdSen + 1); // position of fourth "
        if (fourthSen == string::npos) {
            continue;
        }

        value = commandLine.substr(firstSen + 1, secondSen - firstSen - 1);
        fieldName = commandLine.substr(thirdSen + 1, fourthSen - thirdSen - 1);
        
        outputFile << command << " \"" << value << "\" in \"" << fieldName << "\"" << endl; // print command to output file

        try {
            int result = Inventory.searchInventory(value, fieldName, outputFile);
            if(result == -1) {
                throw runtime_error("Exception: command is wrong"); // check if command is valid
            }
            
        } catch(const runtime_error& e) { // catch if command is invalid
            outputFile << e.what() << endl;
        }
        
        }

        else if (command == "sort") { // if the command is sort imply sort algorithm

        size_t firstSen = commandLine.find('"'); // find first " position
        if (firstSen == string::npos) {
            continue;
        }

        size_t secondSen = commandLine.find('"', firstSen + 1); // find second " position
        if (secondSen == string::npos) {
            continue;
        }

        fieldName = commandLine.substr(firstSen + 1, secondSen - firstSen - 1);

        outputFile << command << " \"" << fieldName << "\"" << endl ; // print command to output file

        try {
            int result = Inventory.sortInventory(fieldName, outputFile); // sort inventory
            if(result == -1) {
                throw runtime_error("Exception: command is wrong"); // check if command is valid
            }
        } catch(const runtime_error& e) {
            outputFile << e.what() << endl;
        }
        }
    }


    for(int i=0; i < Inventory.all_lines.size();i++) { // delete dynamically allocated fields
        for(int j=0; j<Inventory.all_lines[i].line_fields.size(); j++) {
            delete Inventory.all_lines[i].line_fields[j];
        }
    }

    outputFile.close(); // close files
    inputFile.close();
    commandFile.close();

    return 0;
}