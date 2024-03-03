#include <iostream>

using namespace std;

int** createMatrix(int length) {
    int** matrix = new int* [length];
    for (int i = 0; i < length; i++) {
        matrix[i] = new int[length];
        for (int j = 0; j < length; j++) {
            matrix[i][j] = rand() % 10;
        }
    }
        
    return matrix;
}

void printMatrix(int** matrix, int length) {
    for (int i = 0; i < length; i++) {
        for (int j = 0; j < length; j++) {
            cout << matrix[i][j] << ' ';
        }
        
        cout << endl;
    }
}

int main() {
    int length = 3;
    int** matrix = createMatrix(length);
    
    printMatrix(matrix, length);
    
    return 0;
}
