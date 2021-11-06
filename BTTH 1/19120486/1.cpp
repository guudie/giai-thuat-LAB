#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

void printTrace(double* const& arr, int end, double ans){
    double sum = 0;
    int i = end;
    for(; i >= 0; i--){
        sum += arr[i];
        if(sum == ans)
            break;
    }
    for(; i <= end; i++)
        cout << arr[i] << " ";
}

// tính tổng liên tục lớn nhất (cải tiến 2) và lưu lại vị trí cuối cùng của lời giải tối ưu
double largestSum(double* const& arr, int n, int& end){
    double curSum = 0;
    double maxSum = 0;
    for(int i = 0; i < n; i++){
        curSum += arr[i];
        if(curSum > maxSum){
            maxSum = curSum;
            end = i;
        }
        else if(curSum < 0) {
            curSum = 0;
        }
    }

    return maxSum;
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
    
    int end = -1;
    double ans = largestSum(arr, n, end);

    if(end == -1)
        cout << "Tap rong co tong lon nhat";
    else 
        printTrace(arr, end, ans);
    cout << "\n" << ans;
}