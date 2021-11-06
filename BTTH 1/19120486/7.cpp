#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <fstream>
using namespace std;

vector<vector<int>> results;

template<class T>
void printVector(const vector<T>& _v){
    for(auto a : _v)
        cout << a << " ";
}

// giải bài toán túi xách 0-1 bằng cách sinh n bit
int knapsack(int* const& w, int* const& v, bool* chosen, int pos, int n, int weight){
    // nếu pos ra ngoài mảng hoặc giá trị weight đã đạt 0 thì lưu vào danh sách các đáp án có tiềm năng
    if(pos == n || weight == 0){
        vector<int> currentResult;
        for(int i = 0; i < n; i++)
            if(chosen[i])
                currentResult.push_back(i);
        
        if(currentResult.size() > 0)
            results.push_back(currentResult);
        return 0;
    }

    // trường hợp không chọn
    int ans = knapsack(w, v, chosen, pos+1, n, weight);
    // nếu cân nặng của vật pos lớn hơn sức chứa còn lại trong túi
    if(w[pos] > weight)
        return ans;
    
    // trường họp chọn
    chosen[pos] = true;
    ans = max(ans, v[pos] + knapsack(w, v, chosen, pos+1, n, weight-w[pos]));
    chosen[pos] = false;

    return ans;
}

int main(){
    fstream fin("input_7.txt", ios::in);
    int n, weight;
    fin >> weight >> n;

    int* w = new int[n];
    int* v = new int[n];
    bool* chosen = new bool[n];
    for(int i = 0; i < n; i++){
        fin >> w[i] >> v[i];
        chosen[i] = false;
    }

    // tìm tổng giá trị lớn nhất
    int ans = knapsack(w, v, chosen, 0, n, weight);
    
    // tìm đáp án tiềm năng mà có giá trị bằng ans
    for(auto res : results){
        int tmp = 0;
        for(auto a : res){
            tmp += v[a];
        }
        if(tmp == ans){
            printVector(res);
            break;
        }
    }
    cout << "\n" << ans;
}