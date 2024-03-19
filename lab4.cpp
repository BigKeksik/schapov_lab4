#define lenght 4
#include <mpi.h>
#include <iostream>

using namespace std;

void createMatrix(int matrix[lenght][lenght], bool isZero) {
    for (int i = 0; i < lenght; i++) {
        for (int j = 0; j < lenght; j++) {
            if (isZero) {
                matrix[i][j] = 0;
            } else {
                matrix[i][j] = rand() % 10;
            }
        }
    }
}

void printMatrix(int matrix[lenght][lenght]) {
    for (int i = 0; i < lenght; i++) {
        for (int j = 0; j < lenght; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

int main(int argc, char *argv[]) {
    int number = 0;
    int size = 0;
    
    int first[lenght][lenght];
    createMatrix(first, false);

    int second[lenght][lenght];
    createMatrix(second, false);
    
    int result[lenght][lenght];
    createMatrix(result, true);
    
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &number);
    int procLength = lenght / size;

    int procFirst[procLength][lenght], procResult[procLength][lenght];

    MPI_Scatter(first, procLength * lenght, MPI_INT, procFirst, procLength * lenght, MPI_INT, 0, MPI_COMM_WORLD);

    for (int i = 0; i < procLength; i++) {
        for (int j = 0; j < lenght; j++) {
            procResult[i][j] = 0;
            for (int k = 0; k < lenght; k++) {
                procResult[i][j] += procFirst[i][k] * second[k][j];
            }
        }
    }
    
    MPI_Gather(procResult, procLength * lenght, MPI_INT, result, procLength * lenght, MPI_INT, 0, MPI_COMM_WORLD);
    
    if (number == 0) {
        cout << "First:\n";
        printMatrix(first);
        
        cout << "\n\nSecond:\n";
        printMatrix(second);
        
        cout << "\n\nResult:\n";
        printMatrix(result);
    }

    MPI_Finalize();
    
    return 0;
}
