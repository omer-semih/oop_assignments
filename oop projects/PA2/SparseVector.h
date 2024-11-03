#ifndef _SPARSEVECTOR_H_
#define _SPARSEVECTOR_H_

#include <vector>
#include <sstream>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Data { // Represents the elements of vector
    int index;
    double data;
};

class SparseVector { // SPARSE VECTOR CLASS

private:
    vector<Data> alldata; // Private datas
    int max_index;

public:
    
    // NEEDED CONSTRUCTORS
    SparseVector() {};

    SparseVector(vector<Data> Vec, int index);

    SparseVector(string filename);

    bool isNotEmpty(); // Function checks if the SparseVector is empty by checking the size of alldata 

    int getMaxIndex(); // Getter function for max_index

    int getSize(); // Returns the size of vector

    // OVERLOADING FUNCTIONS
    const vector<Data>& getData() const;

    const SparseVector operator +(SparseVector& vector2) const;

    const SparseVector operator -(SparseVector& vector2) const;

    const SparseVector  operator -( ) const;

    const SparseVector& operator=(const SparseVector& vector2);

    friend ostream& operator<<(ostream& os, const SparseVector& vector);

    friend double dot(const SparseVector& vector1,const SparseVector& vector2); // Function calculates the dot product
    
};

#endif