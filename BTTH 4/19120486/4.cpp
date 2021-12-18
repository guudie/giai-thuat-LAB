#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

// thuật toán tìm kiếm nội suy
int interpolSearch(double* arr, int l, int r, double val) {
    if(l>r)
        return -1;
    if(l==r)
        return arr[l] == val? l : -1;
    
    int index = (r-l)*(val-arr[l])/(arr[r]-arr[l]) + l;
    index = max(index, l);
    index = min(index, r);
    if(arr[index] == val)
        return index;
    else if(arr[index] > val)
        return interpolSearch(arr, l, index-1, val);
    else
        return interpolSearch(arr, index+1, r, val);
}

int main() {
    fstream fin("input_4.txt", ios::in);
    int n;
    fin >> n;
    double* arr = new double[n];

    for(int i = 0; i < n; i++)
        fin >> arr[i];
    double val;
    fin >> val;

    cout << interpolSearch(arr, 0, n-1, val);
}