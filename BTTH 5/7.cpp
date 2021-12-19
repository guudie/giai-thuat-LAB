#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

// truy vết các vật có giá trị nhất
void trace(int** dp, int* w, int W, int n) {
    if(n == 0)
        return;
    
    if(dp[n-1][W] == dp[n][W]) {        // nếu không chọn vật n-1 mà dp[n-1][W] vẫn có kết quả
        trace(dp, w, W, n-1);
    }
    else {                              // nếu phải chọn vật n-1 để dp[n][W] có kết quả
        trace(dp, w, W - w[n-1], n-1);
        cout << n-1 << " ";
    }
}

// dp[i][j] lưu tổng giá trị lớn nhất mà tổng khối lượng = j khi xét đến vật i-1
// lưu ý: w và v bắt đầu tại index 0
void knapSack(int* w, int* v, int W, int n) {
    int** dp = new int*[n+1];
    for(int i = 0; i <= n; i++) {
        dp[i] = new int[W+1];
        for(int j = 0; j <= W; j++)
            dp[i][j] = -1;
        dp[i][0] = 0;
    }

    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= W; j++) {
            dp[i][j] = dp[i-1][j];          // lưu giá trị tốt nhất nếu không chọn vật i-1
            if(j >= w[i-1] && dp[i-1][j-w[i-1]] > -1)
                // chọn vật i-1 và so sánh với kết quả tốt nhất với khối lượng = j
                dp[i][j] = max(dp[i][j], dp[i-1][j-w[i-1]] + v[i-1]);
        }
    }

    int ans = 0;
    int opt = 0;
    for(int i = 0; i <= W; i++) {
        if(dp[n][i] > ans) {
            ans = dp[n][i];
            opt = i;
        }
    }
    
    if(ans == 0)
        cout << "Khong co cach chon nao toi uu!";
    else
        trace(dp, w, opt, n);
    cout << "\n" << ans;
}

int main() {
    fstream fin("input_7.txt", ios::in);
    int W, n;
    fin >> W >> n;
    int* w = new int[n];
    int* v = new int[n];
    for(int i = 0; i < n; i++) {
        fin >> w[i] >> v[i];
    }

    knapSack(w, v, W, n);
}