#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <limits>
#include <fstream>
#define inf (int)1e9
using namespace std;

vector<vector<int>> results;

int distance(const vector<int>& res, int** const& g, int n){
    int ans = 0;
    for(int i = 0; i < n; i++){
        ans += g[res[i]][res[i+1]];
    }
    return ans;
}

template<class T>
void printVector(const vector<T>& _v){
    for(auto a : _v)
        cout << a << " ";
}

int tsm(int** const& g, int n, bool* v, int cur, int nodes, int* trace){
    if(nodes == n-1){
        if(g[cur][1] != -1){
            trace[cur] = 1;
            vector<int> currentResult;
            int tmp = 1;
            while(trace[tmp] != 1){
                currentResult.push_back(tmp);
                tmp = trace[tmp];
            }
            currentResult.push_back(cur);
            currentResult.push_back(1);
            results.push_back(currentResult);
            return g[cur][1];
        }
        else
            return inf;
    }

    v[cur] = true;

    int ans = inf;
    for(int i = 1; i <= n; i++){
        if(v[i] || g[cur][i] == -1)
            continue;
        
        trace[cur] = i;
        ans = min(ans, g[cur][i] + tsm(g, n, v, i, nodes+1, trace));
    }

    v[cur] = false;
    return ans;
}

int main(){
    fstream fin("input_5.txt", ios::in);
    int n;
    fin >> n;
    int** g = new int*[n+1];
    bool* v = new bool[n+1];
    int* trace = new int[n+1];
    for(int i = 0; i < n+1; i++){
        g[i] = new int[n+1];
        v[i] = false;
        trace[i] = -1;
        for(int j = 0; j < n+1; j++)
            g[i][j] = -1;
    }
    
    int a, b, c;
    fin >> a;
    while(a != -1){
        fin >> b >> c;
        g[a][b] = g[b][a] = c;
        fin >> a;
    }

    int ans = tsm(g, n, v, 1, 0, trace);
    for(auto a : results){
        if(distance(a, g, n) == ans){
            printVector(a);
            break;
        }
    }
    cout << "\n" << ans;
}