#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#define inf (int)1e9
using namespace std;

// giải thuật chia để trị đổi n xu (rất chậm khi n lớn)
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

int coinsExchange(const vector<int>& arr, int cur, int remaining) {
    if(cur == -1 || remaining < 0)
        return inf;
    if(remaining == 0)
        return 0;
    
    return min(coinsExchange(arr, cur - 1, remaining), coinsExchange(arr, cur, remaining - arr[cur]) + 1);
}

int main() {
    fstream fin("input_6.txt", ios::in);
    int a, k;
    vector<int> arr;
    fin >> a;
    arr.push_back(a);
    while(a != 1) {
        fin >> a;
        arr.push_back(a);
    }

    fin >> k;

    cout << coinsExchange(arr, arr.size()-1, k);
}