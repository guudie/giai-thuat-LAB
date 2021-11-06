#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <math.h>
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

    friend istream& operator>>(istream& is, point& other) {
        is >> other.x >> other.y;
        return is;
    }

    friend ostream& operator<<(ostream& os, const point& other) {
        os << "(" << other.x << ", " << other.y <<")";
        return os;
    }
};

// giải thuật in ra những cặp điểm gần nhất
void closestPts(point* const& arr, int n) {
    double minDist = inf;

    // tìm khoảng cách gần nhất
    for(int i = 0; i < n; i++)
        for(int j = i+1; j < n; j++)
            minDist = min(minDist, arr[i].distance(arr[j]));
    
    // in ra những cặp điểm có khoảng cách bằng minDist
    for(int i = 0; i < n; i++)
        for(int j = i+1; j < n; j++)
            if(arr[i].distance(arr[j]) == minDist)
                cout << arr[i] << " " << arr[j] << "\n";
}

int main(){
    fstream fin("input_3.txt", ios::in);
    int n;
    fin >> n;

    point* arr = new point[n];
    for(int i = 0; i < n; i++)
        fin >> arr[i];
    
    closestPts(arr, n);
}