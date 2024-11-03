#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include "SparseVector.h"
#include "SparseMatrix.h"
using namespace std;

SparseMatrix::SparseMatrix(vector<SparseVector> DATA, vector<int> ROW) {
    
        data = DATA;  // Constructor that takes private members and assigns them 
        row = ROW;    // in the class. It will be used as a return type of overloading operator functions
    }

SparseMatrix::SparseMatrix(string filename) { // Constructor opens file and creates matrix

        ifstream file(filename);
        if (!file.is_open()) {
            cout << "File cannot be opened!" << endl; // Check if the file is opened properly
            return;
        }

        string line; // String to store each line temporarily

        while (getline(file, line)) {
            stringstream ss(line); // Stringstream to parse the line
            
            vector<Data> row_data;
            int row_index;
            
            ss >> row_index;
            row.push_back(row_index);

             Data element; // Data structure to hold element information
            int temp_index; // Temporary variable to hold index
            char separator; // Separator between index and data
            double temp_data; // Temporary variable to hold data
            
            // Read index and data pairs from the stringstream
            while (ss >> temp_index >> separator >> temp_data) {
                element.data = temp_data;
                element.index = temp_index;
                row_data.push_back(element);
            }

            int max;
            max = row_data[row_data.size()-1].index;
            SparseVector row_vec(row_data,max); // Create a SparseVector for the row

            data.push_back(row_vec); // Add the row vector to the data vector
        }

        file.close(); // close file
    }

const SparseMatrix SparseMatrix::operator +(SparseMatrix& matrix2) const {
        
        vector<SparseVector> temp;
        vector<int> tempForRows;
        
        // Find the maximum row index among the two matrices
        int max1=row.back();
        int max2=matrix2.row.back();
        int maximum_row = (max1 >= max2) ? max1 : max2;
        
        // Iterate through rows up to the maximum row index
        for(int i=0;i<=maximum_row;i++) {
            bool found1 = false, found2 = false; // Flags to indicate if row is found in each matrix
            int j=0,k=0;

            while(row[j] != i && row[j] < i && j<row.size()) { // Search for row i in the first matrix
                j++;
            }
            if(row[j] == i) {
                found1 = true; // Set found1 to true if row i is found in the first matrix
            }

            while(matrix2.row[k] != i && matrix2.row[k] < i && k<matrix2.row.size()) { // Search for row i in the second matrix
                k++;
            }
            if(matrix2.row[k] == i) {  // Set found2 to true if row i is found in the second matrix
                found2 = true;
            }

            if(found1 && found2) { // If both rows are found in both matrices, add their corresponding vectors
                temp.push_back(data[j]+matrix2.data[k]);
                tempForRows.push_back(i);
            }
            else if(found1) { // If only row i is found in the first matrix, push its vector to temp
                temp.push_back(data[j]);
                tempForRows.push_back(i);
            }
            else if(found2) { // If only row i is found in the second matrix, push its vector to temp
                temp.push_back(matrix2.data[k]);
                tempForRows.push_back(i);
            }
        }

        return SparseMatrix(temp,tempForRows); // Return a new SparseMatrix constructed from temp vectors and row indices

    }

const SparseMatrix SparseMatrix::operator -(SparseMatrix& matrix2) const {
        
        vector<SparseVector> temp; // Temporary vector to hold result vectors
        vector<int> tempForRows; // Temporary vector to hold indices of non-zero rows

        // Find the maximum row index among the two matrices
        int max1=row.back();
        int max2=matrix2.row.back();
        int maximum_row = (max1 >= max2) ? max1 : max2;
        

        for(int i=0;i<=maximum_row;i++) {
            bool found1 = false, found2 = false; // Flags to indicate if row is found in each matrix
            int j=0,k=0; // Iterators for row vectors of each matrix

            while(row[j] != i && row[j] < i && j<row.size()) { // Search for row i in the first matrix
                j++;
            }
            if(row[j] == i) {
                found1 = true; // Set found1 to true if row i is found in the first matrix
            }

            // Search for row i in the second matrix
            while(matrix2.row[k] != i && matrix2.row[k] < i && k<matrix2.row.size()) {
                k++;
            }
            if(matrix2.row[k] == i) {
                found2 = true; // Set found2 to true if row i is found in the second matrix
            }

            if(found1 && found2) { // If both rows are found in both matrices, subtract their corresponding vectors
                temp.push_back(data[j]-matrix2.data[k]);
                tempForRows.push_back(i);
            }
            else if(found1) { // If only row i is found in the first matrix, push its vector to temp
                temp.push_back(data[j]);
                tempForRows.push_back(i);
            }
            else if(found2) { // If only row i is found in the second matrix, negate its vector and push to temp
                temp.push_back(-matrix2.data[k]);
                tempForRows.push_back(i);
            }
        }

        return SparseMatrix(temp,tempForRows); // Return a new SparseMatrix constructed from temp vectors and row indices

    }

const SparseMatrix SparseMatrix::operator -( ) const {
        
    vector<SparseVector> negate; // Temporary vector to hold negated vectors
    
    // Iterate through each row vector in the matrix
    for(unsigned int i=0;i<data.size();i++) {
        negate.push_back(-data[i]); // Negate each row vector and push to negate vector
    }

    return SparseMatrix(negate, row); // Return a new SparseMatrix with negated vectors and original row indices
}

const SparseMatrix& SparseMatrix::operator=(const SparseMatrix& matrix2) {
        
        // Check for self-assignment
        if (this != &matrix2) { 
        this->data = matrix2.data; // Assign data vector of matrix2 to current object
        this->row = matrix2.row; // Assign row vector of matrix2 to current object
    }
    return *this; // Return a reference to the current object
}

ostream& operator<<(ostream& outputStream, SparseMatrix& matrix) {

    // Iterate through each row of the matrix
    for (unsigned int i = 0; i < matrix.data.size(); i++) {
        // Check if the row is not empty 
        if( matrix.data[i].isNotEmpty()) {
        // Output the row index followed by the corresponding vector representation
        outputStream << matrix.row[i] << " " << matrix.data[i] << endl;
        }
    }
    return outputStream; // Return the output stream
}