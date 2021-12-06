#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <math.h>
#define inf 1e20
using namespace std;

// tọa độ và các hàm bổ trợ
struct coord {
    double x, y;

    double dist(const coord& other) {
        double vx = x - other.x;
        double vy = y - other.y;
        return sqrt(vx*vx + vy*vy);
    }

    static bool compX(const coord& a, const coord b) {          // dùng để sort
        if(a.x == b.x)
            return a.y < b.y;
        return a.x < b.x;
    }

    static bool compY(const coord& a, const coord& b) {         // dùng để sort
        if(a.y == b.y)
            return a.x < b.x;
        return a.y < b.y;
    }

    bool operator<(const coord& other) {                        // dùng để so sánh với median
        if(x == other.x)
            return y < other.y;
        return x < other.x;
    }

    bool operator<=(const coord& other) {                       // dùng để so sánh với median
        if(x == other.x)
            return y <= other.y;
        return x < other.x;
    }

    friend ostream& operator<<(ostream& os, const coord& other) {   // in
        os << "(" << other.x << ", " << other.y << ")";
        return os;
    }
};

// struct lưu các cặp điểm gần nhau, in kết quả
struct trace {
    vector<pair<coord, coord>> list;
    double minDist;

    void print() {
        for(auto a : list) {
            cout << a.first << " " << a.second << "\n";
        }
    }
};

// copy array
template<typename T>
void copy(T* ref, T* const& target, int n) {
    for(int i = 0; i < n; i++)
        ref[i] = target[i];
}

// hàm tính khoảng cách nhỏ nhất giữa các điểm và thêm các cặp điểm tương ứng khi n đủ nhỏ
double closestPairBrute(coord* const& p, int n, trace& t) {
    double ans = inf;

    for(int i = 0; i < n; i++) {
        for(int j = i+1; j < n; j++) {
            double tmp = p[i].dist(p[j]);                   // -- tính khoảng cách
            if(tmp < ans) {                                 // -- đối chiếu với kết quả hiện tại
                ans = tmp;
                if(ans < t.minDist) {                       // nếu ans tốt hơn minDist trong trace thì cập nhật lại trace
                    t.minDist = ans;
                    t.list.clear();
                    t.list.push_back({ p[i], p[j] });       // thêm cặp điểm
                }
                else if(ans == t.minDist) {                 // nếu ans = minDist thì thêm cặp điểm
                    t.list.push_back({ p[i], p[j] });
                }
            }
            else if(tmp == ans && tmp == t.minDist)         // nếu tmp = minDist thì thêm cặp điểm
                t.list.push_back({ p[i], p[j] });
        }
    }
    return ans;
}

// hàm chia để trị tìm khoảng cách nhỏ nhất
// lưu ý: p là con trỏ tới 1 phần tử nhất định của mảng ban đầu, không phải là con trỏ tới phần tử đầu tiên của mảng đó
double closestPairRec(coord* p, coord* q, int n, trace& t) {
    // n đủ nhỏ thì brute force
    if(n <= 3)
        return closestPairBrute(p, n, t);

    // tìm trung vị
    int m = n/2;
    coord median = p[m];

    // chia q thành qL và qR (qL chứa median)
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

    // tính delta
    double dL = closestPairRec(p, qL, m+1, t);
    double dR = closestPairRec(p+m+1, qR, n-m-1, t);
    double d = min(dL, dR);

    // tìm các điểm trong hình chữ nhật l x 2delta
    vector<coord> s;
    for(int i = 0; i < n; i++)
        if(abs(q[i].x - median.x) <= d)
            s.push_back(q[i]);
    
    // tìm khoảng cách nhỏ nhất trong hình chữ nhật l x 2delta
    for(int i = 0; i < s.size(); i++) {
        int j = i + 1;
        while(j < s.size() && abs(s[i].y - s[j].y) <= d) {
            double tmp = s[i].dist(s[j]);
            if(tmp < d) {
                d = tmp;
                t.list.clear();
                t.list.push_back({ s[i], s[j] });
            } else if(tmp == d && s[i] <= median && median < s[j])
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
        p[i] = {x, y};
    }

    closestPair(p, n);
}