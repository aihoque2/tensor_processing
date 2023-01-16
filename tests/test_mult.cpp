#include "../include/matrix.h"
#include <cassert>
#include <bits/stdc++.h>

/*
test_mult.cpp

file to test multiplication
*/

int main(){
    std::vector<std::vector<double>> data1 = {{1.0, 2.0, 3.0}, {4.0,5.0,6.0}, {7.0, 8.0, 9.0},{10.0, 11.0, 12.0}};
    Matrix<double> mat1 = Matrix<double>(data1);
    
    bool bad_flag = false;
    try{
        //test bad matrix (multiply 3x3 and 4x2)
        std::vector<std::vector<double>> badData= {{1.0, 2.0}, {3.0, 4.0}, {5.0, 6.0}, {5.0, 3.0}};
        Matrix<double> badMat = Matrix<double>(badData);
        Matrix<double> badProduct = mat1*badMat;
    }
    catch(...){
        bad_flag = true; //indicated bad matrix passed
    }
    //test multiplication
    std::vector<std::vector<double>> data2= {{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}, {7.0, 8.0, 9.0}};
    std::vector<std::vector<double>> multCheck = {{30.0, 36.0, 42.0}, {66.0, 81.0, 96.0}, {102.0, 126.0, 150.0}, {138.0, 171.0, 204.0}};
    Matrix<double> mat2 = Matrix<double>(data2);
    Matrix<double> product = mat1*mat2;
    //check between 'product' and 'correct' to ensure data is equal between the two
    bool multiply_flag = true;
    for (int i = 0; i < product.getRows(); i++){
        for (int j = 0; j < product.getCols(); j++){
            if (product[i][j] != multCheck[i][j]) multiply_flag = false;
        }
    }
    if (multiply_flag && bad_flag){ 
        return 0;
    }
    else return 1;
}