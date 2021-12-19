#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

typedef pair<int, double> kp;

void optimalBST(kp* key_prob, int n) {
    double* pSum = new double[n];
    pSum[0] = key_prob[0].second;
    for(int i = 1; i < n; i++)
        pSum[i] = pSum[i-1] + key_prob[i].second;
    
    double** dp = new double*[n];
    for(int i = 0; i < n; i++) {
        dp[i] = new double[n];
        dp[i][i] = key_prob[i].second;
    }

    for(int diff = 1; diff < n; diff++) {
        for(int l = 0; l + diff < n; l++) {
            int r = l + diff;
            dp[l][r] = dp[l+1][r];
            for(int t = l+1; t < r; t++) {
                dp[l][r] = min(dp[l][r], dp[l][t-1] + dp[t+1][r]);
            }
            dp[l][r] = min(dp[l][r], dp[l][r-1]);

            dp[l][r] += pSum[r] - pSum[l] + key_prob[l].second;
        }
    }

    cout << dp[0][n-1];
}

int main(){
    fstream fin("input_5.txt", ios::in);
    int n;
    fin >> n;
    kp* key_prob = new kp[n];
    for(int i = 0; i < n; i++)
        fin >> key_prob[i].first >> key_prob[i].second;

    sort(key_prob, key_prob + n);
    optimalBST(key_prob, n);
}