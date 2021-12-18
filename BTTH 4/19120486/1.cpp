#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <queue>
using namespace std;

// thuật toán sắp xếp topo
void topSort(vector<int>* graph, int* inDeg, int n) {
    queue<int> q;
    for(int i = 1; i <= n; i++)
        if(inDeg[i] == 0)
            q.push(i);                  // thêm các đỉnh bậc vào = 0
    
    stringstream ss;
    
    while(!q.empty()) {
        int vert = q.front();
        q.pop();

        ss << vert << " ";
        for(auto a : graph[vert])
            if(--inDeg[a] == 0)         // cập nhật lại đỉnh mà vert có thể tới, thêm vào
                q.push(a);              // hàng đợi nếu đỉnh đó có bậc vào = 0
    }

    for(int i = 1; i <= n; i++)
        if(inDeg[i] > 0) {
            cout << "Khong the sap xep topo\n";
            return;
        }
    
    cout << ss.str();
}

int main() {
    fstream fin("input_1.txt", ios::in);
    int n;
    fin >> n;

    vector<int>* graph = new vector<int>[n+1];
    int* inDeg = new int[n+1]();

    int vertex;
    fin >> vertex;
    while(vertex) {
        int tmp;
        string buffer;
        stringstream ss;
        getline(fin, buffer, '\n');
        ss << buffer;

        while(ss >> tmp) {
            graph[tmp].push_back(vertex);
            inDeg[vertex]++;
        }
        fin >> vertex;
    }

    topSort(graph, inDeg, n);
}