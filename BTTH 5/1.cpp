#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

// in đường đi trong tam giác
void trace(int** dp, int** triangle, int i, int j) {
    if(i == 0) {
        cout << triangle[0][0] << " ";
        return;
    }

    if(j == 0)
        trace(dp, triangle, i-1, j);
    else if(i == j)
        trace(dp, triangle, i-1, j-1);
    else {
        if(dp[i][j] - triangle[i][j] == dp[i-1][j])
            trace(dp, triangle, i-1, j);
        else
            trace(dp, triangle, i-1, j-1);
    }
    
    cout << triangle[i][j] << " ";
}

// giải thuật tìm đường đi có tổng lớn nhất
void triangleSteps(int** triangle, int n) {
    int** dp = new int*[n];
    for(int i = 0; i < n; i++){
        dp[i] = new int[n];
        for(int j = 0; j < n; j++)
            dp[i][j] = 0;
    }
    
    dp[0][0] = triangle[0][0];                      // đỉnh thì có tổng lớn nhất là chính nó
    for(int i = 1; i < n; i++) {
        dp[i][0] = dp[i-1][0] + triangle[i][0];     // nếu ở cạnh trái nhất thì tổng lớn nhất là chính nó + dp[i-1][0]
        for(int j = 1; j <= i; j++) {
            // các điểm còn lại thì dp(i, j) = max(trên, trên_trái) + chính nó; điểm nằm ở cạnh bên phải vẫn là như vậy vì triangle[i][j] >= 0, i,j thuộc n
            dp[i][j] = max(dp[i-1][j], dp[i-1][j-1]) + triangle[i][j];
        }
    }

    // tìm kết quả lớn nhất
    int ans = 0;
    int pos = 0;
    for(int i = 0; i < n; i++) {
        if(dp[n-1][i] > ans) {
            ans = dp[n-1][i];
            pos = i;
        }
    }
    
    cout << ans << "\n";
    trace(dp, triangle, n-1, pos);
}

int main(){
    fstream fin("input_1.txt", ios::in);
    int n;
    fin >> n;
    int** triangle = new int*[n];
    for(int i = 0; i < n; i++){
        triangle[i] = new int[n];
        for(int j = 0; j < n; j++) {
            triangle[i][j] = 0;
            if(j <= i)
                fin >> triangle[i][j];
            // cout << i << ", " << j << "\n";
        }
    }

    triangleSteps(triangle, n);
}