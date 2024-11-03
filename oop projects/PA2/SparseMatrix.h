#ifndef _SPARSEMATRIX_H_
#define _SPARSEMATRIX_H_

#include "SparseVector.h" // Include header file for SparseVector class
using namespace std;

class SparseMatrix {
    
private:
    vector<SparseVector> data; // Vector to store sparse vectors representing rows
    vector<int> row; // Vector to store row indices

public:
    SparseMatrix() {}; // Default constructor

    SparseMatrix(vector<SparseVector> DATA, vector<int> ROW); // Constructor with parameters to initialize SparseMatrix object

    SparseMatrix(string filename); // Constructor that reads matrix data from file

    const SparseMatrix operator +(SparseMatrix& matrix2) const; // Overloaded addition operator for SparseMatrix

    const SparseMatrix operator -(SparseMatrix& matrix2) const; // Overloaded subtraction operator for SparseMatrix

    const SparseMatrix operator -( ) const; // Overloaded unary negation operator for SparseMatrix

    const SparseMatrix& operator=(const SparseMatrix& matrix2); // Overloaded assignment operator for SparseMatrix

    friend ostream& operator<<(ostream& os, SparseMatrix& metrix); // Friend function to overload the output stream operator for SparseMatrix


};

#endif