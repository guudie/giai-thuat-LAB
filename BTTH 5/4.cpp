#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

void traceLIS(int* const& arr, int* const& trace, int i) {
    if(trace[i] == i) {
        cout << arr[i] << " ";
        return;
    }
    traceLIS(arr, trace, trace[i]);
    cout << arr[i] << " ";
}

void LIS(int* const& arr, int n) {
    int* dp = new int[n];
    int* trace = new int[n];
    for(int i = 0; i < n; i++) {
        dp[i] = 1;
        trace[i] = i;
    }
    
    int ans = 1;
    int end = 0;
    for(int i = 1; i < n; i++) {
        for(int j = i-1; j >= 0; j--) {
            if(arr[j] < arr[i]) {
                if(dp[j]+1 > dp[i]) {
                    dp[i] = dp[j]+1;
                    trace[i] = j;
                }
            }
        }
        if(dp[i] > ans) {
            ans = dp[i];
            end = i;
        }
    }

    traceLIS(arr, trace, end);
    cout << "\n" << ans;
}

int main() {
    fstream fin("input_4.txt", ios::in);
    int n;
    fin >> n;
    int *arr = new int[n];
    for(int i = 0; i < n; i++)
        fin >> arr[i];
    
    LIS(arr, n);
}