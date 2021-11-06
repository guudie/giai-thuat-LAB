#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <fstream>
using namespace std;

// sinh dãy n bit, tính tổng và in ra tập con có tổng bằng k
bool subsetSum(int* const& arr, int n, int pos, bool* chosen, int k){
    if(k == 0){
        for(int i = 0; i < n; i++)
            if(chosen[i]) cout << arr[i] << " ";
        cout << "\n";
        return true;
    }

    bool ans = false;
    for(int i = pos; i < n; i++){
        if(arr[i] > k)
            continue;
        
        chosen[i] = true;
        ans |= subsetSum(arr, n, i+1, chosen, k-arr[i]);
        chosen[i] = false;
    }
    return ans;
}

int main(){
    fstream fin("input_6.txt", ios::in);
    int n, k;
    fin >> n;

    int* arr = new int[n];
    bool* chosen = new bool[n];
    for(int i = 0; i < n; i++){
        fin >> arr[i];
        chosen[i] = false;
    }
    fin >> k;

    if(!subsetSum(arr, n, 0, chosen, k))
        cout << "Khong co tap nao co tong bang " << k;
}