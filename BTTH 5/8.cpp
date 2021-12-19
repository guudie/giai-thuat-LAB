#include <iostream>
#include <fstream>
#include <algorithm>
#define inf (int)1e9
using namespace std;

void traceTsm(int** trace, int city, int mask) {
    if(mask == 1) {
        cout << city + 1 << " ";
        return;
    }
    traceTsm(trace, trace[city][mask], mask - (1<<city));
    cout << city + 1 << " ";
}

void tsm(int** graph, int n) {
    int max_mask = (1<<n)-1;
    int** dp = new int*[n];
    int** trace = new int*[n];
    for(int i = 0; i < n; i++) {
        dp[i] = new int[max_mask+1];
        trace[i] = new int[max_mask+1];
        for(int j = 0; j <= max_mask; j++)
            dp[i][j] = inf;
    }

    dp[0][1] = 0;
    trace[0][1] = 0;
    for(int mask = 1; mask <= max_mask; mask++) {
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                if((mask & (1<<i)) && (mask & (1<<j)) && graph[i][j] > -1) {
                    if(dp[j][mask - (1<<i)] + graph[i][j] < dp[i][mask]) {
                        dp[i][mask] = dp[j][mask - (1<<i)] + graph[i][j];
                        trace[i][mask] = j;
                    }
                }
            }
        }
    }

    int ans = inf;
    int end = -1;
    for(int i = 0; i < n; i++) {
        if(graph[i][0] > -1 && dp[i][max_mask] + graph[i][0] < ans) {
            ans = dp[i][max_mask] + graph[i][0];
            end = i;
        }
    }
    if(end == -1)
        cout << "nop---";
    else
        traceTsm(trace, end, max_mask);
    cout << "\n" << ans;
}

int main() {
    fstream fin("input_8.txt", ios::in);
    int n;
    fin >> n;
    int** graph = new int*[n];
    for(int i = 0; i < n; i++) {
        graph[i] = new int[n];
        for(int j = 0; j < n; j++)
            graph[i][j] = -1;
    }

    int a, b, c;
    fin >> a;
    while(a != -1) {
        fin >> b >> c;
        graph[a-1][b-1] = graph[b-1][a-1] = c;
        fin >> a;
    }

    // for(int i = 0; i < n; i++) {
    //     for(int j = 0; j < n; j++){
    //         fin >> graph[i][j];
    //         if(i == j)
    //             graph[i][j] = -1;
    //     }
    // }

    tsm(graph, n);
}