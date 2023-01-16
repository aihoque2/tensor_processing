
#include "../include/matrix.h"
#include <cassert>
/*
test_transpose.cpp

file to test matrix transpose
*/

int main(){
    //test transpose
    std::vector<std::vector<double>> data1 = {{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}, {9.0, 10.0, 11.0}};
    Matrix<double> mat1 = Matrix<double>(data1);

    std::vector<std::vector<double>> transposeCheck= {{1.0, 4.0, 9.0}, {2.0, 5.0, 10.0}, {3.0, 6.0, 11.0}};

    Matrix<double> transpose = mat1.transpose();

    //check between 'transpose' and  'correct' to ensure data is equal between the two
    bool transpose_flag = true;
    for (int i = 0; i < transpose.getRows(); i++){
        for (int j = 0; j< transpose.getCols(); j++){
            if (transpose[i][j] != transposeCheck[i][j]) transpose_flag = false;
        }
    }

    if (transpose_flag){ 
        return 0;
    }
    else return 1;


}