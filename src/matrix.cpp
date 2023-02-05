#ifndef __MATRIX_CPP
#define __MATRIX_CPP

#include "../include/matrix.h"

#define MAX_THREADS 4 //set max_threads accordingly

/*
constructor

create an matrix with a default_value given
@param r: row dimension
@param c: column dimension
@param default_value: default value passed in 
*/
template<typename T>
Matrix<T>::Matrix(unsigned r, unsigned c, const T& default_value){
    numRows = r;
    numCols = c;
    mat.resize(numRows);

    for (int i = 0; i < numRows; i++){
        mat[i].resize(numCols, default_value);
    }
}

/*
constructor

create an matrix from a 2D vector
@param default_value: the 2D vector our matrix is
constructed from 
*/
template<typename T>
Matrix<T>::Matrix(const std::vector<std::vector<T>>& data){
    numRows = data.size();
    numCols = data[0].size();
    mat.reserve(numRows);
    for(int i = 0; i < numRows; i++){
        mat.push_back(data[i]);
    }
}

/*
copy constructor
*/
template<typename T>
Matrix<T>::Matrix(const Matrix &rhs){
    numRows = rhs.numRows;
    numCols = rhs.numCols;

    mat.reserve(numRows);
    mat = rhs.mat;
}

/*
virtual destructor
*/
template<typename T>
Matrix<T>::~Matrix(){}

/*
get rows of the matrix
@return number of rows
*/
template<typename T>
unsigned Matrix<T>::getRows() const{
    return numRows;
}

/*
get columns of the matrix
@return number of colummns
*/
template<typename T>
unsigned Matrix<T>::getCols() const{
    return numCols;
}

/*
Access matrix with [][] operator
enables modification of non-const matrix
@param i: index of the row you wish to access
@return: row of matrix you are indexing
*/
template<typename T>
std::vector<T>& Matrix<T>::operator[](int &i){
    return mat[i];
}

/*
Access matrix with [][] operator
@param i: index of the row you wish to access
@return: row of matrix you are indexing
*/
template<typename T>
const std::vector<T>& Matrix<T>::operator[](int &i) const{
    return mat[i];
}

/*
Matrix Multiplication
@param rhs: Matrix you want to multiply with
@return: Matrix product 
*/
template<typename T>
Matrix<T> Matrix<T>::operator*(const Matrix<T>& rhs){
    unsigned r2 = rhs.getRows();
    if (numCols != r2){
        throw std::invalid_argument("row length of right-hand-side matrix must equal column length of left-hand-side matrix");
    } //assert multicplications

    Matrix<T> product = Matrix(numRows, rhs.getCols(), 0.0);

    std::vector<std::thread> threads;
    for (int i = 0; i < numRows; i++){
        threads.emplace_back(std::thread(&Matrix<T>::multiplyMatrix, this, i, std::ref(rhs), std::ref(product)));
        if (threads.size() >= MAX_THREADS || i == numRows - 1){
            for (int k = 0; k < threads.size(); k++){
                threads[k].join(); 
            }
            threads.clear();
        }
    }
    
    return product; 
}

/*
Matrix transpose
@return transposed matrix
*/
template<typename T>
Matrix<T> Matrix<T>::transpose() const{
    Matrix<T> result = Matrix(numCols, numRows, 0.0);    
    std::vector<std::thread> threads;
    for (int i = 0; i < numRows; i++){
        threads.emplace_back(std::thread(&Matrix<T>::transposeRow, this, i, std::ref(result)));
        if (threads.size() >= MAX_THREADS || i == numRows - 1){
            for (int k = 0; k < threads.size(); k++){
                threads[k].join(); 
            }
            threads.clear();
        }
    }

    return result;
}

//private helpers used for threading in
//multiplication and tranposing

template<typename T>
void Matrix<T>::multiplyMatrix(int i, const Matrix<T>& rhs, Matrix<T>& product){
    for (int j =0; j < rhs.getCols(); j++){
        for (int k = 0; k < numCols; k++){
            product[i][j] += mat[i][k]*rhs[k][j];
        }
    }
}

template<typename T>
void Matrix<T>::transposeRow(int i, Matrix<T>& result) const{
    for (int j =0; j < numCols; j++){
        result[j][i] = mat[i][j];
    }
}
#endif