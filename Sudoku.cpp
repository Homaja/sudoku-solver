#include <iostream>
#include <vector>

using namespace std;

const int N = 9;

// Function to print the Sudoku grid
void printGrid(const vector<vector<int>>& grid) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cout << grid[i][j] << " ";
        }
        cout << endl;
    }
}

// Function to check if a digit can be placed in the given row
bool isSafeInRow(const vector<vector<int>>& grid, int row, int num) {
    for (int col = 0; col < N; ++col) {
        if (grid[row][col] == num) {
            return false;
        }
    }
    return true;
}

// Function to check if a digit can be placed in the given column
bool isSafeInCol(const vector<vector<int>>& grid, int col, int num) {
    for (int row = 0; row < N; ++row) {
        if (grid[row][col] == num) {
            return false;
        }
    }
    return true;
}

// Function to check if a digit can be placed in the given 3x3 box
bool isSafeInBox(const vector<vector<int>>& grid, int startRow, int startCol, int num) {
    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 3; ++col) {
            if (grid[row + startRow][col + startCol] == num) {
                return false;
            }
        }
    }
    return true;
}

// Function to check if a digit can be placed at the given position
bool isSafe(const vector<vector<int>>& grid, int row, int col, int num) {
    return isSafeInRow(grid, row, num) &&
           isSafeInCol(grid, col, num) &&
           isSafeInBox(grid, row - row % 3, col - col % 3, num);
}

// Function to find the next empty cell in the Sudoku grid
bool findEmptyCell(const vector<vector<int>>& grid, int& row, int& col) {
    for (row = 0; row < N; ++row) {
        for (col = 0; col < N; ++col) {
            if (grid[row][col] == 0) {
                return true;
            }
        }
    }
    return false;
}

// Recursive function to solve the Sudoku puzzle
bool solveSudoku(vector<vector<int>>& grid) {
    int row, col;
    if (!findEmptyCell(grid, row, col)) {
        return true; // All cells filled
    }

    for (int num = 1; num <= 9; ++num) {
        if (isSafe(grid, row, col, num)) {
            grid[row][col] = num;
            if (solveSudoku(grid)) {
                return true;
            }
            grid[row][col] = 0; // Undo the current cell
        }
    }
    return false; // Backtrack
}

int main() {
    vector<vector<int>> grid(N, vector<int>(N));

    cout << "Enter the Sudoku grid (9x9):\n";
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cin >> grid[i][j];
        }
    }

    if (solveSudoku(grid)) {
        cout << "Solution:\n";
        printGrid(grid);
    } else {
        cout << "No solution exists.\n";
    }

    return 0;
}