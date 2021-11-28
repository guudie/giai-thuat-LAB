#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#define inf (int)1e9
using namespace std;

int coinsExchange(const vector<int>& arr, int remaining) {
    for(auto a : arr)
        if(a == remaining)
            return 1;
    
    int ans = remaining;
    for(auto a : arr) {
        if(remaining > a) {
            int tmp = 1 + coinsExchange(arr, remaining - a);
            ans = min(ans, tmp);
        }
    }

    return ans;
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

    cout << coinsExchange(arr, k);
}