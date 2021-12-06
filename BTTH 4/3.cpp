#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

// thuật toán partition, phân hoạch các số nhỏ hơn arr[pivot] bên trái, lơn hơn hoặc bằng arr[pivot] bên phải
int partition(double* arr, int l, int r) {
    int j = l-1;
    int pivot = l + rand()%(r - l + 1);
    swap(arr[pivot], arr[r]);

    for(int i = l; i < r; i++) {
        if(arr[i] < arr[r]) {
            j++;
            swap(arr[i], arr[j]);
        }
    }
    j++;
    swap(arr[j], arr[r]);
    return j;
}

// thuật toán chọn số nhỏ thứ k
double kthSelection(double* arr, int n, int k) {
    k--;
    int l = 0;
    int r = n-1;
    int pi = partition(arr, 0, n-1);
    while(1) {
        if(pi == k)
            return arr[pi];
        if(pi < k)
            l = pi+1;
        else
            r = pi-1;
        
        pi = partition(arr, l, r);
    }
} 

int main(){
    fstream fin("input_3.txt", ios::in);
    int n, k;
    fin >> n;
    double* arr = new double[n];
    for(int i = 0; i < n; i++)
        fin >> arr[i];
    fin >> k;

    cout << kthSelection(arr, n, k);
}