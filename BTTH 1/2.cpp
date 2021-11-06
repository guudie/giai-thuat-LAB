#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#define inf (int)1e9
using namespace std;

vector<vector<int>> results;

// hàm tính tổng các phần tử trong vector
template<class T>
T vectorSum(vector<T> v){
    T ans = 0;
    for(auto a : v)
        ans += a;
    return ans;
}

// giải thuật quay lui tìm số lượng xu nhỏ nhất đổi ra lượng 'remaining'
int minExchange(int* const& coins, int cur, int* cnt, int n, int remaining){
    if(remaining == 0){                                 // nếu lượng còn lại = 0 thì lưu vào tập các đáp án tiềm năng
        vector<int> currentResult;
        for(int i = 0; i < n; i++)
            currentResult.push_back(cnt[i]);
        results.push_back(currentResult);
        return 0;
    }
    if(cur == n)                                        // giá trị mặc định khi remaining != 0
        return inf;                                     // và con trỏ cur đã đi quá mảng coins
    
    int ans = inf;
    for(int i = 0; i <= remaining/coins[cur]; i++){     // lặp qua những số lượng có thể cho coins[cur] và gọi đệ quy
        cnt[cur] = i;
        ans = min(ans, i + minExchange(coins, cur+1, cnt, n, remaining - i*coins[cur]));
    }
    cnt[cur] = 0;

    return ans;
}

int main(){
    fstream fin("input_2.txt", ios::in);
    int k;
    int n = 1;
    int tmp;
    fin >> tmp;
    while(tmp != 1){
        fin >> tmp;
        n++;
    }
    fin.close();

    int* coins = new int[n];
    int* cnt = new int[n];
    fin.open("input_2.txt", ios::in);
    for(int i = 0; i < n; i++){
        fin >> coins[i];
        cnt[i] = 0;
        //cout << coins[i] << " ";
    }
    fin >> k;

    // lượng xu nhỏ nhất
    int ans = minExchange(coins, 0, cnt, n, k);

    // lặp qua danh sách chứa lượng xu, tìm ra danh sách có lượng xu nhỏ nhất (= ans)
    for(int i = 0; i < results.size(); i++){
        if(vectorSum(results[i]) == ans){
            for(int j = 0; j < n; j++)
                cout << coins[j] << ": " << results[i][j] << "\n";
            break;
        }
    }
}