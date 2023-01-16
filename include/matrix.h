#ifndef __MATRIX_H
#define __MATRIX_H

#include <iostream>
#include <thread>
#include <vector>

template <typename T>
class Matrix{
    public:
        // constructors
        Matrix(unsigned r, unsigned c, const T& default_value);
        Matrix(const std::vector< std::vector<T> >& data);
        Matrix(const Matrix<T>& rhs);
        ~Matrix();

        //getters
        unsigned getRows() const; //return number of rows
        unsigned getCols() const; //return number of cols
        
        // operators
        std::vector<T> &operator[](int &i); // access elements of the matrix
        const std::vector<T> &operator[](int &i) const;
        
        Matrix<T> operator*(const Matrix<T>& rhs); // multiplication

        Matrix<T> transpose(); // transpose

    private:
        void multiplyMatrix(int i, const Matrix<T>& rhs, Matrix<T>& product);
        void transposeRow(int i, Matrix<T>& result);
        std::vector< std::vector<T> > mat;
        unsigned numRows;
        unsigned numCols;
};


#include "../src/matrix.cpp"
#endif