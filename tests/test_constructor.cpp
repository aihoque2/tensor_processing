#include "../include/matrix.h"
#include <cassert>
/*
test_constructor.cpp

file to test constructor
*/


int main(){
    
    //test constructor
    std::vector<std::vector<double>> data1 = {{1.0, 2.0, 3.0}, {4.0,5.0,6.0}};
    Matrix<double> mat1 = Matrix<double>(data1);
    bool constructor_flag = true;
    for (int i = 0; i < data1.size(); i++){
        for (int j = 0; j < data1[0].size(); j++){
            if (mat1[i][j] != data1[i][j]) constructor_flag = false; 
        }
    }

    Matrix<double> mat2 = Matrix<double>(mat1);
    for (int i = 0; i < mat1.getRows(); i++){
        for (int j = 0; j < mat1.getCols(); j++){
            if (mat2[i][j] != mat1[i][j]) constructor_flag = false; 
        }
    }

    if (constructor_flag) return 0;    
    else return 1;
    
}