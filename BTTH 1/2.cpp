#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
using namespace std;

vector<vector<int>> results;

template<class T>
T vectorSum(vector<T> v){
    T ans = 0;
    for(auto a : v)
        ans += a;
    return ans;
}

int minExchange(int* const& coins, int cur, int* cnt, int n, int remaining){
    if(remaining == 0){
        vector<int> currentResult;
        for(int i = 0; i < n; i++)
            currentResult.push_back(cnt[i]);
        results.push_back(currentResult);
        return 0;
    }
    if(cur == n)
        return 9999;
    
    int ans = 9999;
    for(int i = 0; i <= remaining/coins[cur]; i++){
        if(remaining - i*coins[cur] < 0)
            break;
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

    int ans = minExchange(coins, 0, cnt, n, k);
    for(int i = 0; i < results.size(); i++){
        if(vectorSum(results[i]) == ans){
            for(int j = 0; j < n; j++)
                cout << coins[j] << ": " << results[i][j] << "\n";
            break;
        }
    }
}