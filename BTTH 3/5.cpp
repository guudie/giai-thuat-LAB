/*
    *-- Thuật toán chia để trị tìm đa giác lồi của 1 tập điểm S.
    - Sử dụng thuật toán quick hull.
    - Giải thích thuật toán:

    Tại bước đầu tiên, nhận thấy rằng, 2 điểm cực A(x_min, y) và B(x_max, y) của S luôn nằm trên đa giác lồi H,
    ta thêm 2 điểm này vào H rồi chia S ra 2 nửa (trên, dưới) và gọi hàm tìm các điểm trên đa giác với 2 phần đó.
    
    Tại bước 2, tìm điểm cực P (xa đoạn thẳng AB nhất), nhận thấy rằng P cũng nằm trong H (nếu không thì phải có
    điểm P' nào đó có khoảng cách d(P', AB) > d(P, AB)--mâu thuẫn), ta thêm P vào H và có tam giác ABP. Nhận thấy
    các điểm nằm trong ABP không thể nằm trên đa giác nên loại các điểm đó, tiếp tục gọi hàm để tìm các điểm trên
    đa giác ở ngoài tam giác ABP từ 2 cạnh AP và BP.

    Tại bước i > 2, làm tương tự bước 2 nhưng cạnh AB trở thành AP hoặc BP.
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include <algorithm>
using namespace std;

template<typename T>
void printVector(const vector<T>& v) {
    for(auto a : v)
        cout << a << " ";
}

// struct tọa độ
struct coord {
    double x, y;
    coord(double _x = 0, double _y = 0) : x(_x), y(_y) {}

    // trả về độ dài (vector)
    double len() {
        return sqrt(x*x + y*y);
    }

    // tìm tọa độ z của tích có hướng (vector)
    double crossLen(const coord& other) {
        return x*other.y - y*other.x;
    }

    coord& operator=(const coord& other) {
        x = other.x;
        y = other.y;
        return *this;
    }

    coord operator-(const coord& other) {
        coord tmp(x-other.x, y-other.y);
        return tmp;
    }

    bool operator<(const coord& other) {
        if(x == other.x)
            return y < other.y;
        return x < other.x;
    }

    friend ostream& operator<<(ostream& os, const coord& other) {
        os << "(" << other.x << ", " << other.y << ")";
        return os;
    }
};

/*                                                                                      o
    thuật toán quick hull                                                             o    o
    chú ý: hàm chỉ xét các điểm nằm ở phía bên trái của vector AB (điểm o):      A -----------> B
                                                                                    x  x 
                                                                                       x   x
*/
void convex_hull(const vector<coord>& S, vector<coord>& H, coord A, coord B) {
    if(S.size() == 0)       // nếu không còn điểm để xét
        return;

    coord AB = B - A;       // vector AB
    coord P = S[0];
    double pDist = abs((P-A).crossLen(AB))/AB.len();

    // tìm điểm cực P
    for(auto t : S) {
        double cross = (t-A).crossLen(AB);
        if(cross >= 0)
            continue;
        
        double d = -cross/AB.len();
        if(d > pDist) {
            pDist = d;
            P = t;
        }
    }
    
    H.push_back(P);
    coord BP = P - B;
    coord PA = A - P;

    // tìm các điểm nằm bên trái PB và AP
    vector<coord> outerBP;
    vector<coord> outerPA;
    for(auto t : S) {
        if((t-A).crossLen(AB) >= 0)
            continue;
        if((t-B).crossLen(BP) > 0)
            outerBP.push_back(t);
        else if((t-P).crossLen(PA) > 0)
            outerPA.push_back(t);
    }

    // chia để trị
    convex_hull(outerBP, H, P, B);
    convex_hull(outerPA, H, A, P);
}

vector<coord> find_hull(vector<coord>& S) {
    if(S.size() < 3)                    // nếu không đủ điểm thì không xét
        return vector<coord>(0);
    
    sort(S.begin(), S.end());
    
    vector<coord> H;
    H.push_back(S[0]);                  // thêm A
    H.push_back(S[S.size()-1]);         // thêm B

    convex_hull(S, H, H[0], H[1]);      // xây dựng đa giác với các điểm bên trái (A, B)
    convex_hull(S, H, H[1], H[0]);      // xây dựng đa giác với các điểm bên trái (B, A)
    return H;
}

int main() {
    fstream fin("input_5.txt", ios::in);
    int n;
    fin >> n;
    vector<coord> S;
    for(int i = 0; i < n; i++) {
        double x, y;
        fin >> x >> y;
        S.push_back({x, y});
    }

    printVector(find_hull(S));
}