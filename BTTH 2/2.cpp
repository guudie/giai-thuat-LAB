#include <iostream>
#include <fstream>
using namespace std;

int x[8] = { 2, 2, -2, -2, 1, 1, -1, -1 };
int y[8] = { -1, 1, 1, -1, 2, -2, 2, -2 };

void printBoard(int** const& board, int n) {
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++)
            cout << board[i][j] << " ";
        cout << "\n";
    }
}

bool knightTour(int** const& board, int row, int col, int occupied, int n) {
    if(occupied == n*n) {
        printBoard(board, n);
        return true;
    }

    for(int i = 0; i < 8; i++) {
        
    }
}

int main() {

}