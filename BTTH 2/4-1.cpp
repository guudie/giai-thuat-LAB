#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
using namespace std;

vector<vector<int>> results;

template<class T>
void printVector(const vector<T>& v) {
    for(auto a : v)
        cout << a << " ";
}

// cách 1: lặp qua từ cur đến cuối và gọi đệ quy tại i+1
void subsetSum(int* const& arr, int n, int cur, bool* chosen, int total) {
    if(total == 0) {
        vector<int> currentResult;
        for(int i = 0; i < n; i++)
            if(chosen[i])
                currentResult.push_back(arr[i]);
        results.push_back(currentResult);
        return;
    }

    for(int i = cur; i < n; i++) {
        if(total < arr[i])
            continue;

        chosen[i] = true;
        subsetSum(arr, n, i+1, chosen, total-arr[i]);
        chosen[i] = false;
    }
}

int main() {
    fstream fin("input_4.txt", ios::in);
    int n, k;
    fin >> n;
    int* arr = new int[n];
    bool* chosen = new bool[n];
    for(int i = 0; i < n; i++) {
        fin >> arr[i];
        chosen[i] = false;
    }
    fin >> k;

    subsetSum(arr, n, 0, chosen, k);
    if(results.size() == 0)
        cout << "No answer!";
    for(auto a : results) {
        printVector(a);
        cout << "\n";
    }
}