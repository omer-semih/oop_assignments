#include <iostream>
#include <fstream>
#include <string>   // Including necessary libraries
#include <vector>            
#include <sstream>             
#include "SparseVector.h"
#include "SparseMatrix.h"
using namespace std;

bool SparseVector::isNotEmpty() { // Function checks if the SparseVector is empty by 
        if(alldata.size() > 0 ) return true; // checking the size of alldata vector
        else return false;
    }

int SparseVector::getMaxIndex() { // Getter function for max_index
        return max_index;
    }

int SparseVector::getSize() { // Returns the size of vector
        return alldata.size();
    }

const vector<Data>& SparseVector::getData() const { // Getter function for alldata vector
    return alldata;
}

SparseVector::SparseVector(vector<Data> Vec, int index) { // constructor takes private members and assigns them to class
        alldata = Vec;
        max_index = index;
    }

SparseVector::SparseVector(string filename) { // constructor opens a file and reads it. Creates SparseVector

        max_index = 0; // initialize max index with 0

        ifstream cinfromfile;
        cinfromfile.open(filename); // open file

        if (!cinfromfile.is_open()) {
            cout << "File cannot be opened!" << endl; // check if the file opened properly
            return;
        }

        int a; // variable to store index
        double b; // variable to store data of element
        char c; // char variable to read ":" from the file
       
        while (cinfromfile>>a>>c>>b) { // Read elements of vector one by one
        
        Data newData; // temp struct that would be pushed to vector
        newData.index = a;
        newData.data = b;
        alldata.push_back(newData); // push struct to vector

        if (a > max_index) // Check if the read index is larger than current maximum index
            max_index = a;
        }

        cinfromfile.close(); // close file after reading
    }

const SparseVector SparseVector::operator +(SparseVector& vector2) const { // '+' operator overloading

    vector<Data> sum; // stores summed vectors
    int maximum_index = (max_index >= vector2.max_index) ? max_index : vector2.max_index; // determine largest index

    for(int i=0;i<=maximum_index;i++) {
        
        bool foundOne=false, foundTwo=false;
        int j=0, k=0;

        if(i <= max_index) { // Search in first vector if index occurs in 
            while(j < alldata.size() && alldata[j].index < i) {  // stop if index is larger than the index to be found
                j++;
            }
            if(j < alldata.size() && alldata[j].index == i) {
                foundOne = true; // set flag if found
            }
        }

        if(i<=vector2.max_index) { // Search in second vector if index occurs in
            while(k < vector2.alldata.size() && vector2.alldata[k].index < i) { // stop if index is larger than the index to be found
                k++;
            }
            if(k < vector2.alldata.size() && vector2.alldata[k].index == i) {
                foundTwo = true; // // set flag if found
            }
        }

        if(foundOne && foundTwo) { // If both found push their sum
            if((alldata[j].data + vector2.alldata[k].data) != 0) { // check if the sum is zero or not
            Data temp;
            temp.index=i;
            temp.data = (alldata[j].data + vector2.alldata[k].data);
            sum.push_back(temp);
            }
            
        }
        else if(foundOne) { // If only found in one then push only this one
            Data temp;
            temp.index=i;
            temp.data = alldata[j].data;
            sum.push_back(temp);
        }
        else if(foundTwo) { // If only found in two then push only this one
            Data temp;
            temp.index=i;
            temp.data = vector2.alldata[k].data;
            sum.push_back(temp);
        }

    }

    return SparseVector(sum, maximum_index); // return their sum by constructor
}

const SparseVector SparseVector::operator -(SparseVector& vector2) const { // '-' operator overloading
    
    vector<Data> substract;
    int maximum_index = (max_index >= vector2.max_index) ? max_index : vector2.max_index; // determine largest index

    for(int i=0;i<=maximum_index;i++) { // Search in first vector if index occurs in 
        
        bool foundOne=false, foundTwo=false;
        int j=0, k=0;

        if(i <= max_index) { 
            while(j < alldata.size() && alldata[j].index < i) { // stop if index is larger than the index to be found
                j++;
            }
            if(j < alldata.size() && alldata[j].index == i) {
                foundOne = true; // set flag if found
            }
        }

        if(i<=vector2.max_index) {
            while(k < vector2.alldata.size() && vector2.alldata[k].index < i) { // stop if index is larger than the index to be found
                k++;
            }
            if(k < vector2.alldata.size() && vector2.alldata[k].index == i) {
                foundTwo = true; // set flag if found
            }
        }

        if(foundOne && foundTwo) { // If found in both then push their substraction
            if((alldata[j].data - vector2.alldata[k].data) != 0) { // check if the subs is zero or not
            Data temp;
            temp.index=i;
            temp.data = (alldata[j].data - vector2.alldata[k].data);
            substract.push_back(temp);
            }
            
        }
        else if(foundOne) { // If only found in first then push only this one
            Data temp;
            temp.index=i;
            temp.data = alldata[j].data;
            substract.push_back(temp);
        }
        else if(foundTwo) { // If only found in second then push negative of this one
            Data temp;
            temp.index=i;
            temp.data = (-vector2.alldata[k].data);
            substract.push_back(temp);
        }

    }

    return SparseVector(substract, maximum_index); // return their substraction by constructor
}

const SparseVector  SparseVector::operator -( ) const { // '-' operator overloading (unary)

    vector<Data> negate;
    Data temp;

    for(unsigned int i=0;i<alldata.size();i++) { // travel one by one and push it's negatiated value
        temp.data = alldata[i].data*(-1);
        temp.index = alldata[i].index;
        negate.push_back(temp);
    }

    return SparseVector(negate, max_index); // return negatiated vector
}

const SparseVector& SparseVector::operator=(const SparseVector& vector2) { // '=' operator overloading

    if (this != &vector2) {  // if current object is not same with parameter then make them equal
        this->alldata = vector2.alldata;
        this->max_index = vector2.max_index;
    }
    return *this; // return current object
}

ostream& operator<<(ostream& outputStream, const SparseVector& vector) { // '<<' operator overloading

    for (unsigned int i = 0; i < vector.alldata.size(); i++) {
        outputStream << vector.alldata[i].index << ":" << vector.alldata[i].data << " "; // cout in desired format
    }

    return outputStream;
}

double dot(const SparseVector& vector1,const SparseVector& vector2) { // function calculates dot product of a vector

    // determine maximum index
    int maximum_index = (vector1.max_index >= vector2.max_index) ? vector1.max_index : vector2.max_index; 
    double totalSum=0; // variable stores the total sum of dot product

    for(int i=0;i<=maximum_index;i++) {
        
        bool foundOne=false, foundTwo=false;
        int j=0, k=0;

        if(i <= vector1.max_index) { // condition not to go outside of boundaries
            while(j < vector1.alldata.size() && vector1.alldata[j].index < i) {
                j++;
            }
            if(j < vector1.alldata.size() && vector1.alldata[j].index == i) { // check if the index is found
                foundOne = true;
            }
        }

        if(i<=vector2.max_index) { // condition not to go outside of boundaries
            while(k < vector2.alldata.size() && vector2.alldata[k].index < i) {
                k++;
            }
            if(k < vector2.alldata.size() && vector2.alldata[k].index == i) {  // check if the index is found
                foundTwo = true;
            }
        }

        if(foundOne && foundTwo) { // if found it both then it means the result is different than zero
            totalSum += (vector1.alldata[j].data * vector2.alldata[k].data);
        }

    }

    return totalSum; // return sumation
}