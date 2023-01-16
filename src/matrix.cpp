#ifndef __MATRIX_CPP
#define __MATRIX_CPP

#include "../include/matrix.h"

#define MAX_THREADS 2 //set max_threads accordingly

template<typename T>
Matrix<T>::Matrix(unsigned r, unsigned c, const T& default_value){
    numRows = r;
    numCols = c;
    mat.resize(numRows);

    for (int i = 0; i < numRows; i++){
        mat[i].resize(numCols, default_value);
    }
}

template<typename T>
Matrix<T>::Matrix(const std::vector<std::vector<T>>& data){
    numRows = data.size();
    numCols = data[0].size();
    mat.reserve(numRows);
    for(int i = 0; i < numRows; i++){
        mat.push_back(data[i]);
    }
}

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

template<typename T>
unsigned Matrix<T>::getRows() const{
    return numRows;
}

template<typename T>
unsigned Matrix<T>::getCols() const{
    return numCols;
}

template<typename T>
std::vector<T>& Matrix<T>::operator[](int &i){
    return mat[i];
}

template<typename T>
const std::vector<T>& Matrix<T>::operator[](int &i) const{
    return mat[i];
}

template<typename T>
Matrix<T> Matrix<T>::operator*(const Matrix<T>& rhs){
    unsigned r2 = rhs.getRows();
    if (numCols != r2){
        throw std::invalid_argument("row length of matrix 2 must equal column length of matrix 1");
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

template<typename T>
Matrix<T> Matrix<T>::transpose() const{

    Matrix<T> result = Matrix(numCols, numRows, 0.0);

    for (int i = 0; i < numRows; i++){
        for(int j = 0; j < numCols; j++){
            result[j][i] = this->mat[i][j];
        }
    }

    return result;
}


/*
template<typename T>
Matrix<T> Matrix<T>::transpose() const{
    
    Matrix<T> result = Matrix(numCols, numRows, 0.0);    
    std::vector<std::thread> threads;
    for (int i = 0; i < numRows; i++){
        threads.emplace_back(std::thread(&Matrix<T>::transposeRow, this, i, result));
        if (threads.size() >= MAX_THREADS || i == numRows - 1){
            for (int k = 0; k < threads.size(); k++){
                threads[k].join(); 
            }
            threads.clear();
        }
    }

    return result;
}
*/

template<typename T>
void Matrix<T>::multiplyMatrix(int i, const Matrix<T>& rhs, Matrix<T>& product){
    for (int j =0; j < rhs.getCols(); j++){
        for (int k = 0; k < numCols; k++){
            product[i][j] += mat[i][k]*rhs[k][j];
        }
    }
}

template<typename T>
void Matrix<T>::transposeRow(int i, Matrix<T>& result){
    for (int j =0; j < numCols; j++){
        result[j][i] = mat[i][j];
    }
}
#endif