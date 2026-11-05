#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>

using namespace std;

class Matrix {
private:
    int size;
    vector<vector<int>> data;

public:
    Matrix(int n = 0) : size(n), data(n, vector<int>(n, 0)) {}
    
    int getSize() const { return size; }
    
    void setElement(int r, int c, int val) {
        if (r >= 0 && r < size && c >= 0 && c < size) {
            data[r][c] = val;
        }
    }

    // Print matrix with alignment
    void printMat() const {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                cout << setw(4) << data[i][j] << " ";
            }
            cout << "\n"; 
        }
    }

    // 2. Add matrices using operator overloading
    Matrix operator+(const Matrix& other) const {
        Matrix result(size);
        for (int i = 0; i < size; i++)
            for (int j = 0; j < size; j++)
                result.data[i][j] = data[i][j] + other.data[i][j];
        return result;
    }

    // 3. Multiply matrices using operator overloading
    Matrix operator*(const Matrix& other) const { 
        Matrix result(size);
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                int sum = 0;
                for (int k = 0; k < size; k++) {
                    sum += data[i][k] * other.data[k][j];
                }
                result.data[i][j] = sum;
            }
        }
        return result;
    }

    // 4. Diagonal sums
    void printDiagonalSums() const {
        int mainDiag = 0, secDiag = 0;
        for (int i = 0; i < size; i++) {
            mainDiag += data[i][i];
            secDiag += data[i][size - 1 - i];
        }
        cout << "Main diagonal sum: " << mainDiag << "\n"; 
        cout << "Secondary diagonal sum: " << secDiag << "\n"; 
    }

    // 5. Swap rows
    Matrix swapRows(int r1, int r2) const {
        Matrix result = *this; 
        if (r1 < 0 || r1 >= size || r2 < 0 || r2 >= size) {
            cout << "Invalid row index\n";
            return result;
        }
        vector<int> t = result.data[r1];
        result.data[r1] = result.data[r2];
        result.data[r2] = t;
        return result;
    }

    // 6. Swap columns
    Matrix swapColumns(int c1, int c2) const {
        Matrix result = *this; 
        if (c1 < 0 || c1 >= size || c2 < 0 || c2 >= size) {
            cout << "Invalid column index\n"; 
            return result;
        }
        for (int i = 0; i < size; i++) {
            int t = result.data[i][c1];
            result.data[i][c1] = result.data[i][c2];
            result.data[i][c2] = t;
        }
        return result;
    }

    // 7. Update element
    Matrix updateElement(int row, int col, int newVal) const {
        Matrix result = *this; 
        if (row < 0 || row >= size || col < 0 || col >= size) {
            cout << "Invalid position\n"; 
            return result;
        }
        result.data[row][col] = newVal;
        return result;
    }
};

int main(int argc, char* argv[]) {
    const char* inputFileName = (argc > 1) ? argv[1] : "input.txt";
    ifstream file(inputFileName);
    if (!file) {
        cout << "Error opening file: " << inputFileName << "\n"; 
        return 1;
    }

    int N;
    file >> N;
    if (N <= 0) {
        cout << "Invalid N\n"; 
        return 1;
    }

    Matrix A(N), B(N);
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++) {
            int val;
            file >> val;
            A.setElement(i, j, val);
        }

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++) {
            int val;
            file >> val;
            B.setElement(i, j, val);
        }
    file.close();

    cout << "Matrix A:\n"; // Fixed: Single line
    A.printMat();

    cout << "\nMatrix B:\n"; // Fixed: Single line
    B.printMat();

    cout << "\nA + B:\n"; // Fixed: Single line
    Matrix C = A + B;
    C.printMat();

    cout << "\nA * B:\n"; // Fixed: Single line
    Matrix D = A * B;
    D.printMat();

    cout << "\nDiagonal sums for Matrix A:\n"; // Fixed: Single line
    A.printDiagonalSums();

    int r1, r2;
    cout << "\nEnter two row indices to swap: "; // Fixed: Single line
    cin >> r1 >> r2;
    cout << "Problem 5 - Rows " << r1 << " and " << r2 << " swapped:\n"; // Fixed: Single line
    Matrix swappedRowsMat = A.swapRows(r1, r2);
    swappedRowsMat.printMat();

    int c1, c2;
    cout << "\nEnter two column indices to swap: "; // Fixed: Single line
    cin >> c1 >> c2;
    cout << "Problem 6 - Columns " << c1 << " and " << c2 << " swapped:\n"; // Fixed: Single line
    Matrix swappedColsMat = A.swapColumns(c1, c2);
    swappedColsMat.printMat();

    int row, col, newVal;
    cout << "\nEnter row, column, and new value to update: "; // Fixed: Single line
    cin >> row >> col >> newVal;
    cout << "Problem 7 - Updated matrix:\n"; // Fixed: Single line
    Matrix updatedMat = A.updateElement(row, col, newVal);
    updatedMat.printMat();

    return 0;
}