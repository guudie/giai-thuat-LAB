#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#define inf (int)1e9
using namespace std;

// giải thuật chia để trị đổi n xu (remaining, rất chậm khi n lớn và mệnh giá xu nhỏ)
int coinsExchange(const vector<int>& arr, int remaining) {
    if(remaining == 0)
        return 0;
    
    int ans = remaining;
    int tmp;
    for(auto a : arr) {
        if(remaining >= a) {
            tmp = 1 + coinsExchange(arr, remaining - a);
            ans = min(ans, tmp);
        }
    }

    return ans;
}

// in đáp án
void printAnswer(const vector<int>& arr, int* const& trace) {
    for(int i = 0; i < arr.size(); i++)
        cout << arr[i] << ": " << trace[i] << "\n";
}

// tìm đáp án với số lượng xu: coins; và số tiền: remaining
bool findAnswer(const vector<int>& arr, int* trace, int cur, int remaining, int coins) {
    if(remaining == 0 && coins == 0) {
        printAnswer(arr, trace);
        return true;
    }

    if(cur >= arr.size())
        return false;

    for(int i = 0; i <= coins; i++) {
        if(arr[cur]*i > remaining)
            continue;
        trace[cur] = i;
        if(findAnswer(arr, trace, cur+1, remaining - arr[cur]*i, coins-i))
            return true;
    }
    trace[cur] = 0;
    return false;
}

int main() {
    fstream fin("input_6.txt", ios::in);
    int a, n;
    vector<int> arr;
    fin >> a;
    arr.push_back(a);
    while(a != 1) {
        fin >> a;
        arr.push_back(a);
    }
    int* trace = new int[arr.size()];
    
    fin >> n;

    int ans = coinsExchange(arr, n);
    findAnswer(arr, trace, 0, n, ans);
}