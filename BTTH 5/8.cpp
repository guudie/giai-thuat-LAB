#include <iostream>
#include <fstream>
#include <algorithm>
#define inf (int)1e9
using namespace std;

// truy vết chu trình ngắn nhất
// lưu ý: city bắt đầu từ 0 nên khi in ra cộng thêm 1
void traceTsm(int** trace, int city, int mask) {
    if(mask == 1) {
        cout << city + 1 << " ";
        return;
    }
    traceTsm(trace, trace[city][mask], mask - (1<<city));
    cout << city + 1 << " ";
}

// dp[i][mask] là giá trị đường đi nhỏ nhất từ thành phố 0 đến i, trong đó các thành phố trong biểu diễn nhị phân của <mask> đã được đi qua
// ví dụ: dp[2][13] là đường đi nhỏ nhất từ 0 -> 2, trong đó các thành phố 0, 2, 3 đã được đi qua (13 = 1101)
// khi đó: dp[i][mask] = min{ dp[j][mask - (1<<i)] + graph[i][j] }, trong đó j là 1 thành phố trong <mask> mà có đường đi tới i
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

    dp[0][1] = 0;               // đường đi từ tp 0 -> 0 là 0
    trace[0][1] = 0;            // truy vết chính nó
    
    for(int mask = 1; mask <= max_mask; mask++) {                                   // lặp qua các tập có thể
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {                                            // lặp qua các cặp i, j
                if((mask & (1<<i)) && (mask & (1<<j)) && graph[i][j] > -1) {        // kiểm tra i, j có trong mask và có đường đi từ j -> i hay không
                    if(dp[j][mask - (1<<i)] + graph[i][j] < dp[i][mask]) {
                        dp[i][mask] = dp[j][mask - (1<<i)] + graph[i][j];           // chọn kết quả tối ưu nhất
                        trace[i][mask] = j;                                         // và lưu dấu truy vết
                    }
                }
            }
        }
    }

    int ans = inf;
    int end = -1;
    for(int i = 0; i < n; i++) {                                                    // tìm thành phố cuối chu trình (end) có đường đi từ 0 -> end
        if(graph[i][0] > -1 && dp[i][max_mask] + graph[i][0] < ans) {               // cộng với graph(end, 0) là ngắn nhất
            ans = dp[i][max_mask] + graph[i][0];
            end = i;
        }
    }

    if(end == -1)
        cout << "Khong the tim thay duong di toi uu!";
    else {
        traceTsm(trace, end, max_mask);
        cout << "1\n" << ans;
    }
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

    tsm(graph, n);
}