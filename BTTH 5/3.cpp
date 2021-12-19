#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

// truy vết tìm dãy con chung dài nhất
void trace(string str1, string str2, int** dp) {
    int n = str1.length();
    int m = str2.length();
    string res = "";

    while(n && m) {
        if(str1[n-1] == str2[m-1] && dp[n-1][m-1] + 1 == dp[n][m]) {
            res += str1[n-1];
            n--;
            m--;
        }
        else {
            if(dp[n][m] == dp[n-1][m])
                n--;
            else
                m--;
        }
    }

    reverse(res.begin(), res.end());
    cout << res;
}

// dp[i][j] là độ dài dãy con chung dài nhất khi xét tới ký tự thứ i (bắt đầu từ 1) của str1, ký tự thứ j (bắt đầu từ 1) của str2
// tại vị trí (i, j), một là độ dài dãy con dài nhất nằm ở vị trí (i-1, j)
//                    hai là nằm ở vị trí (i, j-1)
//                    nếu str1[i-1] == str2[j-1] thì cũng có thể nằm ở vị trí (i-1, j-1) và thêm 1
// lưu ý: string str1 và str2 bắt đầu từ index 0
void LCS(string str1, string str2) {
    int n = str1.length();
    int m = str2.length();
    int** dp = new int*[n+1];
    for(int i = 0; i <= n; i++) {
        dp[i] = new int[m+1];
        for(int j = 0; j <= m; j++)
            dp[i][j] = 0;
    }

    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
            if(str1[i-1] == str2[j-1])
                dp[i][j] = max(dp[i][j], dp[i-1][j-1] + 1);
        }
    }

    if(!dp[n][m])
        cout << "Khong co day con chung!";
    else
        trace(str1, str2, dp);
}

int main() {
    fstream fin("input_3.txt", ios::in);
    string str1, str2;
    fin >> str1 >> str2;

    LCS(str1, str2);
}