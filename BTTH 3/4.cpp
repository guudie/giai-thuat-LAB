#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <math.h>
#define inf 1e20
using namespace std;

struct coord {          // tọa độ và vị trí trong mảng
    double x, y;
    int pos;

    double dist(const coord& other) {
        double vx = x - other.x;
        double vy = y - other.y;
        return sqrt(vx*vx + vy*vy);
    }

    static bool compX(const coord& a, const coord b) {
        if(a.x == b.x)
            return a.y < b.y;
        return a.x < b.x;
    }

    static bool compY(const coord& a, const coord& b) {
        if(a.y == b.y)
            return a.x < b.x;
        return a.y < b.y;
    }

    friend ostream& operator<<(ostream& os, const coord& other) {
        os << "(" << other.x << ", " << other.y << ")";
        return os;
    }
};

struct trace {
    vector<pair<coord, coord>> list;
    double minDist;

    void print() {
        for(auto a : list) {
            cout << a.first << " " << a.second << "\n";
        }
    }
};

template<typename T>
void copy(T* ref, T* const& target, int n) {
    for(int i = 0; i < n; i++)
        ref[i] = target[i];
}

double closestPairBrute(coord* const& p, int n, trace& t) {
    double ans = inf;
    for(int i = 0; i < n; i++)
        for(int j = i+1; j < n; j++) {
            double tmp = p[i].dist(p[j]);
            if(tmp < ans) {
                ans = tmp;
                if(ans < t.minDist) {
                    t.minDist = ans;
                    t.list.clear();
                    t.list.push_back({ p[i], p[j] });
                }
                else if(ans == t.minDist)
                    t.list.push_back({ p[i], p[j] });
            }
            else if(tmp == ans && tmp == t.minDist)
                t.list.push_back({ p[i], p[j] });
        }
    return ans;
}

double closestPairRec(coord* p, coord* q, int n, trace& t) {
    if(n <= 3)
        return closestPairBrute(p, n, t);
    
    int m = n/2;
    //m += n&1;
    coord median = p[m];

    coord* qL = new coord[m+1];
    coord* qR = new coord[n-m-1];
    int iL = 0;
    int iR = 0;
    for(int i = 0; i < n; i++) {
        if(p[i].x < median.x) {
            qL[iL] = p[i];
            iL++;
        }
        else if(p[i].x > median.x) {
            qR[iR] = p[i];
            iR++;
        }
        else {
            if(p[i].y <= median.y) {
                qL[iL] = p[i];
                iL++;
            }
            else {
                qR[iR] = p[i];
                iR++;
            }
        }
    }

    double dL = closestPairRec(p, qL, m+1, t);
    double dR = closestPairRec(p+m+1, qR, n-m-1, t);
    double d = min(dL, dR);

    vector<coord> s;
    for(int i = 0; i < n; i++)
        if(abs(q[i].x - median.x) <= d)
            s.push_back(q[i]);
    
    for(int i = 0; i < s.size(); i++) {
        int j = i + 1;
        while(j < s.size() && abs(s[i].y - s[j].y) <= d) {
            double tmp = s[i].dist(s[j]);
            if(tmp < d) {
                d = tmp;
                t.list.clear();
                t.list.push_back({ s[i], s[j] });
            } else if(tmp == d)
                t.list.push_back({ s[i], s[j] });
            j++;
        }
    }

    delete[] qL;
    delete[] qR;
    return d;
}

void closestPair(coord* p, int n) {
    sort(p, p+n, coord::compX);
    for(int i = 0; i < n; i++)
        p[i].pos = i;
    coord* q = new coord[n];
    copy<coord>(q, p, n);
    sort(q, q+n, coord::compY);

    trace t;
    t.minDist = inf;

    closestPairRec(p, q, n, t);
    t.print();
}

int main() {
    fstream fin("input_4.txt", ios::in);
    int n;
    fin >> n;
    coord* p = new coord[n];
    for(int i = 0; i < n; i++) {
        double x, y;
        fin >> x >> y;
        p[i] = {x, y, -1};
    }

    closestPair(p, n);
}