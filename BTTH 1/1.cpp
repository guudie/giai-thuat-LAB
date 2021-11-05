#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

double largestSum(double* const& arr, int n, int& start, int& end){
    double ans = 0;
    start = end = -1;
    for(int i = 0; i < n; i++){
        double sum = 0;
        for(int j = i; j < n; j++){
            sum += arr[j];
            if(sum > ans){
                start = i;
                end = j;
                ans = sum;
            }
        }
    }

    return ans;
}

int main(){
    fstream fin("input_1.txt", ios::in);
    int n;
    fin >> n;
    double* arr = new double[n];
    for(int i = 0; i < n; i++){
        fin >> arr[i];
        //cout << arr[i] << " ";
    }
    
    int start = -1;
    int end = -1;
    double ans = largestSum(arr, n, start, end);

    if(start == -1){
        cout << "Tap rong\n";
    }
    else {
        for(int i = start; i <= end; i++)
            cout << arr[i] << " ";
        cout << "\n";
    }
    cout << ans;
}