#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

typedef pair<int, double> kp;       // {key, xác suất}

// phép duyệt giữa với mảng truy vết
// trace[l][r] chứa nút gốc của cây nhị phân lập được từ l -> r
void inOrder(int** trace, int l, int r) {
    if(l > r)                   // nếu không thể đi tiếp
        return;
    
    if(l == r) {                // nếu tới nút lá
        cout << l + 1 << " ";
        return;
    }

    int t = trace[l][r];        // tìm nút gốc từ đoạn l -> r, duyệt giữa 2 đoạn còn lại
    inOrder(trace, l, t-1);
    cout << t + 1 << " ";
    inOrder(trace, t+1, r);
}

// dp[l][r] chứa kết quả tốt nhất cho đoạn từ l -> r
void optimalBST(kp* key_prob, int n) {
    sort(key_prob, key_prob + n);                   // vì là cây nhị phân TÌM KIẾM nên cần sort theo key nếu chưa sort sẵn

    double* pSum = new double[n];                   // pSum[i] = tổng tần suất của các key từ index 0 -> i
    pSum[0] = key_prob[0].second;
    for(int i = 1; i < n; i++)
        pSum[i] = pSum[i-1] + key_prob[i].second;
    
    double** dp = new double*[n];
    int** trace = new int*[n];
    for(int i = 0; i < n; i++) {
        dp[i] = new double[n];
        trace[i] = new int[n];

        dp[i][i] = key_prob[i].second;              // cây nhị phân tìm kiếm tối ưu nhất với 1 nút là chính nó
        trace[i][i] = i;                            //
    }

    // duyệt các cặp l, r theo thứ tự tăng dần về độ dài (diff = r - l)
    for(int diff = 1; diff < n; diff++) {
        for(int l = 0; l + diff < n; l++) {
            int r = l + diff;

            // tìm t tối ưu nhất để dp[l][t-1] + dp[t+1][r] nhỏ nhất
            dp[l][r] = dp[l+1][r];
            trace[l][r] = l;
            for(int t = l+1; t < r; t++) {
                if(dp[l][r] > dp[l][t-1] + dp[t+1][r]) {
                    dp[l][r] = dp[l][t-1] + dp[t+1][r];
                    trace[l][r] = t;
                }
            }
            if(dp[l][r] > dp[l][r-1]) {
                dp[l][r] = dp[l][r-1];
                trace[l][r] = r;
            }

            // cộng dp[l][r] với tổng xác suất từ l -> r
            dp[l][r] += pSum[r] - pSum[l] + key_prob[l].second;
        }
    }

    inOrder(trace, 0, n-1);
    cout << "\n" << trace[0][n-1] + 1;
}

int main(){
    fstream fin("input_5.txt", ios::in);
    int n;
    fin >> n;
    kp* key_prob = new kp[n];
    for(int i = 0; i < n; i++)
        fin >> key_prob[i].first >> key_prob[i].second;

    optimalBST(key_prob, n);
}