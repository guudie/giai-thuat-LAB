#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

// in vị trí của các quân hậu trên các dòng [1..n]
void printPos(int* const& pos, int n, stringstream& ss) {
    for(int i = 0; i < n; i++)
        ss << pos[i] + 1 << " ";
    ss << "\n";
}

// kiểm tra xem các quân hậu có ăn nhau hay không
bool possible(int* const& pos, int row, int col, int n) {
    int j = 1;
    for(int i = row-1; i >= 0; i--) {
        // kiểm tra ăn dọc
        if(pos[i] == col)
            return false;
        
        // kiểm tra ăn chéo
        if(col - j >= 0 && pos[i] == col - j)
            return false;
        if(col + j < n && pos[i] == col + j)
            return false;
        j++;
    }
    return true;
}

void queens(int row, int* const& pos, int n, int& ans, stringstream& ss) {    // pos[i]: vị trí của 1 quân hậu trên dòng i
    if (row == n) {
        ans++;
        printPos(pos, n, ss);
        return;
    }
    
    for(int i = 0; i < n; i++) {
        pos[row] = i;
        if(!possible(pos, row, i, n))
            continue;
        
        queens(row + 1, pos, n, ans, ss);
    }
    pos[row] = -1;
}

int main() {
    fstream fin("input_1.txt", ios::in);
    stringstream ss;
    int n;
    int ans = 0;
    fin >> n;
    int* pos = new int[n];
    for(int i = 0; i < n; i++)
        pos[i] = -1;
    
    queens(0, pos, n, ans, ss);
    cout << ans << "\n" << ss.str();
}