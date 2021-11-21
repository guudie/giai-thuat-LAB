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

// kiểm tra ô có bị chiếm hoặc ngoài phạm vi hay không
bool check(int** const& board, int row, int col, int n) {
    if(row >= n || row < 0 || col >= n || col < 0)
        return false;
    if(board[row][col] != -1)
        return false;
    return true;
}

// tìm đường đi cho quân mã
bool knightTour(int** const& board, int row, int col, int occupied, int n) {    // occupied = số ô đi qua
    // nếu tất cả các ô đã được đi qua thì in kết quả và dừng chương trình
    if(occupied == n*n) {
        printBoard(board, n);
        return true;
    }

    // đi qua các ô có thể tới và gọi đệ quy, sau đó quay lui
    for(int i = 0; i < 8; i++) {
        if(!check(board, row+x[i], col+y[i], n))
            continue;
        
        board[row+x[i]][col+y[i]] = occupied;
        if(knightTour(board, row+x[i], col+y[i], occupied+1, n))
            return true;
        board[row+x[i]][col+y[i]] = -1;
    }
    return false;
}

int main() {
    fstream fin("input_2.txt", ios::in);
    int n;
    fin >> n;
    int** board = new int*[n];
    for(int i = 0; i < n; i++) {
        board[i] = new int[n];
        for(int j = 0; j < n; j++)
            board[i][j] = -1;
    }

    bool b = false;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++) {
            board[i][j] = 0;
            if(knightTour(board, i, j, 1, n)) {
                b = true;
                break;
            }
            board[i][j] = -1;
        }
        if(b)
            break;
    }
}