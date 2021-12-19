#include <iostream>
#include <fstream>
#include <algorithm>
#include <stack>
using namespace std;

// in stack chứa dãy đã được truy vết
void printStack(const stack<int>& s) {
    for(stack<int> tmp = s; !tmp.empty(); tmp.pop())
        cout << tmp.top() << " ";
}

// truy vết tất cả các dãy có tổng j khi xét tới i (bắt đầu từ 1)
void trace(int* arr, bool** dp, int i, int j, stack<int>& s) {
    if(i == 0) {
        printStack(s);
        cout << "\n";
        return;
    }
    
    // khi không chọn arr[i-1]
    if(dp[i-1][j]) {
        trace(arr, dp, i-1, j, s);
    }
    // khi chọn arr[i-1]
    if(j >= arr[i-1] && dp[i-1][j-arr[i-1]]) {
        s.push(arr[i-1]);
        trace(arr, dp, i-1, j-arr[i-1], s);
        s.pop();
    }
}

// dp[i][j] kiểm tra xem có tập con có tổng = j hay không khi xét đến phần tử thứ i (arr[i-1])
// lưu ý: mảng arr bắt đầu từ index 0
void subsetSum(int* arr, int n, int k) {
    bool** dp = new bool*[n+1];
    for(int i = 0; i <= n; i++) {
        dp[i] = new bool[k+1];
        for(int j = 0; j <= k; j++)
            dp[i][j] = false;
        dp[i][0] = true;
    }

    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= k; j++) {
            dp[i][j] = dp[i-1][j];          // không chọn arr[i-1]
            if(j >= arr[i-1])
                dp[i][j] = dp[i][j] || dp[i-1][j-arr[i-1]];     // chọn arr[i-1]
        }
    }

    if(!dp[n][k]) {
        cout << "Khong co tap con co tong " << k << "!";
        return;
    }

    stack<int> s;
    trace(arr, dp, n, k, s);
}

int main() {
    fstream fin("input_6.txt", ios::in);
    int n, k;
    fin >> n;
    int* arr = new int[n];
    for(int i = 0; i < n; i++)
        fin >> arr[i];
    fin >> k;

    subsetSum(arr, n, k);
}