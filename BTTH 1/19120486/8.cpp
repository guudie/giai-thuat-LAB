#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <fstream>
#define inf (int)1e9
using namespace std;

// in ra bộ công việc của n người
void printJob(int* job, int n){     // job[i] = stt của người được phân công việc i
    for(int i = 0; i < n; i++){
        int j = 0;
        for(; j < n; j++)
            if(job[j] == i)
                break;
        
        cout << j + 1 << " ";
    }
}

// tìm tập ánh xạ có chi phí bằng chi phí nhỏ nhất (total)
void find(int** const& c, int* job, int cur, int n, int total){
    if(cur == n){
        printJob(job, n);
        cout << "\n";
    }

    for(int i = 0; i < n; i++){
        if(job[i] != -1 || total < c[cur][i])
            continue;
        
        job[i] = cur;
        find(c, job, cur+1, n, total-c[cur][i]);
        job[i] = -1;
    }
}

// tìm chi phí nhỏ nhất
int jobAssignment(int** const& c, bool* occupied, int cur, int n){
    if(cur == n)
        return 0;
    
    int ans = inf;
    for(int i = 0; i < n; i++){
        if(occupied[i])
            continue;
        
        occupied[i] = true;
        ans = min(ans, c[cur][i] + jobAssignment(c, occupied, cur+1, n));
        occupied[i] = false;
    }
    return ans;
}

int main(){
    fstream fin("input_8.txt", ios::in);
    int n;
    fin >> n;

    int** c = new int*[n];
    int* job = new int[n];
    bool* occupied = new bool[n];
    for(int i = 0; i < n; i++){
        c[i] = new int[n];
        job[i] = -1;
        occupied[i] = false;
        for(int j = 0; j < n; j++)
            fin >> c[i][j];
    }

    int ans = jobAssignment(c, occupied, 0, n);
    cout << ans << "\n";

    find(c, job, 0, n, ans);
}