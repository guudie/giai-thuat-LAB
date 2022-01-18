#include <bits/stdc++.h>
using namespace std;

int rec(int n) {
    if(n <= 1)
        return 1;
    int ans = 0;
    for(int i = 0; i < n; i++)
        ans += rec(i)*rec(n-i-1);
    return ans;
}

int dp(int n) {
    int* c = new int[n+1];
    c[0] = c[1] = 1;
    for(int i = 2; i <= n; i++) {
        c[i] = 0;
        for(int k = 0; k < i; k++)
            c[i] += c[k]*c[i-k-1];
    }
    return c[n];
}

int main() {
    int n;
    cin >> n;
    cout << rec(n) << " " << dp(n);
}