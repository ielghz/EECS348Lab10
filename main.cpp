#include <iostream>
#include <fstream>
#include <iomanip> 

using namespace std;

const int MAX = 10;

class Matrix {
private:
    int size;
    int data[MAX][MAX];

public:
    Matrix(int n = 0) : size(n) {
        for (int i = 0; i < MAX; i++)
            for (int j = 0; j < MAX; j++)
                data[i][j] = 0;
    }

    int getSize() const { return size; }
    void setSize(int n) { size = n; }

    // 1. Read matrix data from file stream directly into class instances
    void readFromFile(ifstream& file) {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                file >> data[i][j];
            }
        }
    }

    // 1. Display matrix with neat alignment formatting
    void printMat() const {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                cout << setw(4) << data[i][j] << " ";
            }
            cout << "\n";
        }
    }

    // 2. Add two matrices using operator overloading
    Matrix operator+(const Matrix& other) const {
        Matrix result(size);
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                result.data[i][j] = data[i][j] + other.data[i][j];
            }
        }
        return result;
    }

    // 3. Multiply two matrices using operator overloading
    Matrix operator*(const Matrix& other) const {
        Matrix result(size);
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                result.data[i][j] = 0;
                for (int k = 0; k < size; k++) {
                    result.data[i][j] += data[i][k] * other.data[k][j];
                }
            }
        }
        return result;
    }

    // 4. Get the sum of matrix diagonal elements
    void printDiagonalSums() const {
        int mainDiag = 0, secDiag = 0;
        for (int i = 0; i < size; i++) {
            mainDiag += data[i][i];
            secDiag += data[i][size - 1 - i];
        }
        cout << "Main Diagonal: " << mainDiag << "\nSecondary Diagonal: " << secDiag << "\n";
    }

    // 5. Swap matrix rows - Passed strictly BY VALUE to fulfill lab requirements.
    friend Matrix swapRows(Matrix m, int r1 = 0, int r2 = 1) {
        if (r1 < 0 || r1 >= m.size || r2 < 0 || r2 >= m.size) {
            cout << "Invalid row index\n";
            return m;
        }
        for (int j = 0; j < m.size; j++) {
            int t = m.data[r1][j];
            m.data[r1][j] = m.data[r2][j];
            m.data[r2][j] = t;
        }
        return m;
    }

    // 6. Swap matrix columns - Passed strictly BY VALUE.
    friend Matrix swapColumns(Matrix m, int c1 = 0, int c2 = 1) {
        if (c1 < 0 || c1 >= m.size || c2 < 0 || c2 >= m.size) {
            cout << "Invalid column index\n";
            return m;
        }
        for (int i = 0; i < m.size; i++) {
            int t = m.data[i][c1];
            m.data[i][c1] = m.data[i][c2];
            m.data[i][c2] = t;
        }
        return m;
    }

    // 7. Update matrix element - Passed strictly BY VALUE.
    friend Matrix updateElement(Matrix m, int row = 0, int col = 0, int newVal = 100) {
        if (row < 0 || row >= m.size || col < 0 || col >= m.size) {
            cout << "Invalid position\n";
            return m;
        }
        m.data[row][col] = newVal;
        return m;
    }
};

int main(int argc, char* argv[]) {
    const char* inputFileName = "input.txt";
    if (argc > 1){
        inputFileName = argv[1];
    }

    ifstream file(inputFileName);
    if (!file) {
        cout << "Error opening file: " << inputFileName << "\n";
        return 1;
    }

    int N;
    file >> N;
    if (N <= 0 || N > MAX) {
        cout << "Invalid N\n";
        file.close();
        return 1;
    }

    Matrix A(N), B(N);
    A.readFromFile(file);
    B.readFromFile(file);
    file.close();


    cout << "=== Matrix A ===\n"; A.printMat();
    cout << "\n=== Matrix B ===\n"; B.printMat();

    cout << "\n=== Addition (A + B) ===\n";
    Matrix C = A + B;
    C.printMat();

    cout << "\n=== Multiplication (A * B) ===\n";
    Matrix D = A * B;
    D.printMat();

    cout << "\n=== Diagonal Sums (A) ===\n";
    A.printDiagonalSums();

    int r1, r2;
    cout << "\n=== Problem 5: Swap Rows ===\n";
    cout << "Enter two row indices to swap: ";
    cin >> r1 >> r2;
    cout << "Resulting matrix:\n";
    Matrix swappedRowsMat = swapRows(A, r1, r2);
    swappedRowsMat.printMat();

    int c1, c2;
    cout << "\n=== Problem 6: Swap Columns ===\n";
    cout << "Enter two column indices to swap: ";
    cin >> c1 >> c2;
    cout << "Resulting matrix:\n";
    Matrix swappedColsMat = swapColumns(A, c1, c2);
    swappedColsMat.printMat();

    int row, col, newVal;
    cout << "\n=== Problem 7: Update Element ===\n";
    cout << "Enter row index, column index, and new value: ";
    cin >> row >> col >> newVal;
    cout << "Resulting matrix:\n";
    Matrix updatedMat = updateElement(A, row, col, newVal);
    updatedMat.printMat();

    return 0;
}