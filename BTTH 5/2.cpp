#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#define inf (int)1e9
using namespace std;

// truy vết lượng xu mỗi mệnh giá
void trace(const vector<int>& coins, int** dp, int money) {
    int n = coins.size();
    int* cnt = new int[n];
    for(int i = 0; i < n; i++)
        cnt[i] = 0;

    int i = n;
    while(money) {
        if(dp[i-1][money] == dp[i][money]) {
            i--;
        }
        else {
            cnt[i-1]++;
            money -= coins[i-1];
        }
    }

    for(i = 0; i < n; i++)
        cout << coins[i] << ": " << cnt[i] << "\n";
}

// dp[i][j] là lượng xu nhỏ nhất đổi được khi xét đến xu thứ i (bắt đầu từ 1), lượng tiền j
// lượng xu mỗi mệnh giá không giới hạn nên một là không chọn:                     -->  dp[i-1][j];
//                                          hai là chọn thêm 1 xu cùng mệnh giá:   -->  dp[i-1][j-coins[i-1]] + 1
void coinChange(const vector<int>& coins, int money) {
    int n = coins.size();
    int** dp = new int*[n+1];
    for(int i = 0; i <= n; i++) {
        dp[i] = new int[money+1];
        dp[i][0] = 0;
        for(int j = 1; j <= money; j++)
            dp[i][j] = inf;
    }

    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= money; j++) {
            dp[i][j] = dp[i-1][j];
            if(j >= coins[i-1])
                dp[i][j] = min(dp[i][j-coins[i-1]] + 1, dp[i-1][j]);
        }
    }
    
    trace(coins, dp, money);
}

int main() {
    fstream fin("input_2.txt", ios::in);
    vector<int> coins;
    int a;
    while(fin >> a)
        coins.push_back(a);
    
    int money = coins[coins.size()-1];
    coins.pop_back();

    coinChange(coins, money);
}