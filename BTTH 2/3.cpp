#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#define inf (int)1e9
using namespace std;

typedef pair<int, int> ii;      // điểm -- khoảng cách
vector<vector<ii>> results;

int sumDist(const vector<ii>& v) {
    int res = 0;
    for(int i = 0; i < v.size()-1; i++)
        res += v[i].second;
    return res;
}

void printVector(const vector<ii>& v) {
    for(auto a : v)
        cout << a.first << " ";
}

int tsm(vector<ii>* const& g, int n, int cur, int nodes, bool* visited, ii* trace) {
    if(nodes == n-1) {
        int i = 0;
        for(; i < g[cur].size(); i++)
            if(g[cur][i].first == 1)
                break;
        
        if(i != g[cur].size()) {
            trace[cur] = { 1, g[cur][i].second };
            ii tmp = trace[cur];
            vector<ii> currentResult;
            while(1) {
                currentResult.push_back(tmp);
                tmp = trace[tmp.first];
                if(tmp.first == 1)
                    break;
            }
            currentResult.push_back(trace[cur]);
            results.push_back(currentResult);
            return g[cur][i].second;
        }
        else
            return inf;
    }

    visited[cur] = true;
    int ans = inf;
    for(auto a : g[cur]) {
        if(visited[a.first])
            continue;
        
        trace[cur] = a;
        ans = min(ans, a.second + tsm(g, n, a.first, nodes+1, visited, trace));
    }
    visited[cur] = false;
    return ans;
}

int main() {
    fstream fin("input_3.txt", ios::in);
    int n, a, b, c;
    fin >> n;
    vector<ii>* g = new vector<ii>[n+1];
    ii* trace = new ii[n+1];
    bool* visited = new bool[n+1];

    for(int i = 0; i <= n; i++)
        visited[i] = false;

    fin >> a;
    while(a != -1) {
        fin >> b >> c;
        g[a].push_back({ b, c});
        g[b].push_back({ a, c});
        fin >> a;
    }

    int ans = tsm(g, n, 1, 0, visited, trace);
    if(ans >= inf)
        cout << "No answer!\n";
    else {
        for(auto v : results){
            if(sumDist(v) == ans) {
                printVector(v);
                break;
            }
        }
        cout << "\n" << ans;
    }
}