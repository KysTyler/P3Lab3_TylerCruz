/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: Tyler C
 *
 * Created on October 30, 2020, 1:03 PM
 */

#include <cstdlib>
#include <iostream>
#include <valarray>

using namespace std;

/*
 * 
 */

int** GenerateMatrix(int);
void FreeMatrix(int**&, int);
void printMatrix(int**&, int);
int** fillMatrix(int**& matrix, int size);
int calculate_negativePositive(int, int);
double** calculateAdjunta(double**, int);
double calculateCofactor(double**&, int, int, int);
double** submatrix(double**&, int, int, int);
double determinante(double**&, int);
int calculate2x2(double**&, int);
double** transpuesta(double**&, int);
double** inverse(double**& ,double ,int );
double** GenerateMatrix1(int);
void printMatrix1(double**& matrix, int size);

int main(int argc, char** argv) {
    int size;
    cout << "Ingrese el tamaño del matriz: " << endl;
    cin >> size;
    int** matrix = new int*[size];
    matrix = GenerateMatrix(size);
    matrix = fillMatrix(matrix, size);
    printMatrix(matrix, size);
    
    //testing submatrix
    double** temp = GenerateMatrix1(size);
    //temp = submatrix(temp, 0, 0, size);
    //cout << endl;
    //printMatrix(temp, size - 1);
    
    //program
    double** N = calculateAdjunta(temp,size);
    double determinante_A = determinante(temp,size);
    //double respuesta = inverse(N,determinante_A,size);


    //Free memory space        
    FreeMatrix(matrix, size);
    return 0;
}

int** GenerateMatrix(int size) {
    if (size > 0) {
        int** charArray = new int*[size];
        for (int i = 0; i < size; i++) {
            charArray[i] = new int[size];
        }
        return charArray;
    }
    return NULL;
}

double** GenerateMatrix1(int size) {
    if (size > 0) {
        double** charArray = new double*[size];
        for (int i = 0; i < size; i++) {
            charArray[i] = new double[size];
        }
        return charArray;
    }
    return NULL;
}

void FreeMatrix(int**& m, int size) {
    if (m != NULL && size > 0) {
        for (int i = 0; i < size; i++) {
            if (m[i] != NULL) {
                delete[] m[i];
                m[i] = NULL;
            }
        }
        delete[] m;
        m = NULL;
    }
}

void printMatrix(int**& matrix, int size) {
    if (size > 0 && matrix != NULL) {
        for (int i = 0; i < size; i++) {
            if (matrix[i] != NULL) {
                for (int j = 0; j < size; j++) {
                    cout << matrix[i][j] << " ";
                }
                cout << endl;
            }
        }
    }
}

void printMatrix1(double**& matrix, int size) {
    if (size > 0 && matrix != NULL) {
        for (int i = 0; i < size; i++) {
            if (matrix[i] != NULL) {
                for (int j = 0; j < size; j++) {
                    cout << matrix[i][j] << " ";
                }
                cout << endl;
            }
        }
    }
}

int** fillMatrix(int**& matrix, int size) {
    if (size > 0 && matrix != NULL) {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                matrix[i][j] = (rand() % 19) - 9;
            }
        }
    }
    return matrix;
}

int calculate_negativePositive(int i, int j) {
    int suma = 0;
    suma = i + j;
    if (suma % 2 == 0) {
        return 1;
    }
    return -1;
}

double** calculateAdjunta(double** matrix, int size) {
    double** temp = GenerateMatrix1(size - 1);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            temp[i][j] = calculateCofactor(temp, i, j, size);
        }
    }
    temp = transpuesta(temp, size);
    return temp;
}

double calculateCofactor(double**& m, int row, int col, int size) {
    double** temp = GenerateMatrix1(size - 1);
    //temp = submatrix(m, row, col, size);
    int calculation;
    calculation = calculate_negativePositive(row, col) * determinante(temp, size - 1);
    return calculation;

}

int** submatrix(int**& m, int row, int col, int size) {
    int mx = 0, ny = 0;
    int** temp = GenerateMatrix(size);
    cout << size - 1 << "size - 1" << endl;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            cout << "I  ---> " << i << endl;
            cout << "J ----> " << j << endl;
            if (i != row && j != col) {
                cout << "[" << mx << "]" << "[" << ny << "]" << "THiS " << endl;
                temp[mx][ny] = m[i][j];
                //cout<< "A" << "["<<temp[mx][ny]<<"]" << endl;
                //cout<< "B" << "["<<m[i][j]<<"]" << endl;
                ny++;
            }

            if (ny == size - 1) {
                mx++;
                ny = 0;
            }
        }
    }
    return temp;
}

double determinante(double**& m, int size) {
    int valor = 0;
    if (size == 2) {
        valor = calculate2x2(m, size);
    } else {
        for (int i = 0; i < size; i++) {
            valor += m[0][i] * calculateCofactor(m, 0, i, size);
        }
    }
    return valor;
}

int calculate2x2(double**& m, int size) {
    int diagonal = 0, inverserDiagonal = 0, result;
    diagonal += m[0][0] * m[1][1];
    inverserDiagonal += m[0][1] * m[1][0];
    result = diagonal - inverserDiagonal;
    return result;
}

double** transpuesta(double**& m, int size) {
    double** temp = GenerateMatrix1(size);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            temp[i][j] = m[j][i];
        }
    }
    return temp;
}

double** inverse(double**& m,double determinante,int size){
    double** K = GenerateMatrix1(size);
    for(int i = 0;i< size;i++){
        for(int j = 0;j<size;j++){
            K[i][j] = 1 / (determinante * m[i][j]);
        }
    }
    return K;
}

