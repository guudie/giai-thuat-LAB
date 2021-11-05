#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <limits>
#include <fstream>
#define inf 1e9
using namespace std;

struct point{
    double x, y;
    point(double _x = 0, double _y = 0) : x(_x), y(_y) {}

    // khoảng cách đến điểm khác
    double distance(const point& other) {
        double dx = x-other.x;
        double dy = y-other.y;
        return sqrt(dx*dx + dy*dy);
    }

    // tính tan của vector, nếu cần
    double tan(){
        return y/x;
    }

    bool operator<(const point& other) const{
        if(x == other.x) return y < other.y;
        return x < other.x;
    }

    bool operator>(const point& other) const{
        if(x == other.x) return y > other.y;
        return x > other.x;
    }

    bool operator==(const point& other){
        return x == other.x && y == other.y;
    }

    point& operator=(const point& other){
        x = other.x;
        y = other.y;
        return *this;
    }

    point operator-(const point& other){
        return point(x-other.x, y-other.y);
    }

    friend istream& operator>>(istream& is, point& other) {
        is >> other.x >> other.y;
        return is;
    }

    friend ostream& operator<<(ostream& os, const point& other) {
        os << "(" << other.x << ", " << other.y <<")";
        return os;
    }
};

// hàm phụ sắp xếp
bool comp(const point& a, const point& b){
    return a > b;
}

// in vector
template<class T>
void printVector(const vector<T>& _v){
    for(auto a : _v)
        cout << a << " ";
}

// hàm tìm convex hull
// có thể thấy điểm trái nhất và phải nhất thuộc đa giác
// hàm xây dựng đa giác bắt đầu từ điểm bên trái, xây dựng các điểm bên dưới rồi các điểm phía trên
// các điểm cực này (extreme points); có thể thấy là 2 cạnh bất kì kề nhau thì cạnh trái có độ dốc (tan)
// bé hơn cạnh bên phải đối với cung dưới, cung trên thì ngược lại
void constructHull(vector<point>& pts){
    sort(pts.begin(), pts.end());
    int size = pts.size();
    point cur;
    point lExtreme = pts[0];                    // các điểm cực trái/phải
    point rExtreme = pts[size-1];

    vector<point> hull;

    // thêm tất cả các điểm trái nhất
    int i = 0;
    while(pts[i].x == lExtreme.x){
        hull.push_back(pts[i]);
        i++;
    }
    sort(hull.begin(), hull.end(), comp);

    // xây dựng các điểm dưới
    cur = lExtreme;
    while(cur.x != rExtreme.x){
        double tg = inf;
        for(int j = 0; j < size; j++){
            if(pts[j].x <= cur.x)
                continue;
            
            point v = pts[j] - cur;
            if(tg > v.tan()){
                tg = v.tan();
                i = j;
            }
        }
        cur = pts[i];
        hull.push_back(cur);
    }
    //printVector(hull);

    // thêm tất cả các cạnh phải nhất
    for(i = i+1; i < size; i++)
        hull.push_back(pts[i]);

    // xây dựng các điểm trên
    i = size-1;
    cur = pts[i];
    while(cur.x != lExtreme.x){
        double tg = inf;
        for(int j = size-1; j >= 0; j--){
            if(pts[j].x >= cur.x)
                continue;
            
            point v = pts[j] - cur;
            if(tg > v.tan()){
                tg = v.tan();
                i = j;
            }
        }
        cur = pts[i];
        if(cur.x != lExtreme.x && cur.x != rExtreme.x)
            hull.push_back(cur);
    }

    printVector(hull);
}

int main(){
    fstream fin("input_4.txt", ios::in);
    int n;
    vector<point> pts;
    fin >> n;
    for(int i = 0; i < n; i++){
        point p;
        fin >> p;
        pts.push_back(p);
    }

    constructHull(pts);
}