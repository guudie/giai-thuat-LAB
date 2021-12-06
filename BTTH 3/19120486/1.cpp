#include <iostream>
#include <fstream>
using namespace std;

// tìm bit cao nhất (most significant bit)
int msb(long long a) {
    if(a == 0)
        return 0;
    
    // giảm a cho tới khi chỉ còn lại bit cao nhất
    while(a - (a&-a))
        a -= a&-a;
    
    // tìm vị trí của bit cao nhất
    int i = 0;
    while((a & (1<<i)) == 0)
        i++;
    return i+1;
}

// giải thuật chia để trị tính tích 2 số lớn (lập trình trên bit)
long long mul(long long x, long long y) {
    int n = max(msb(x), msb(y));        // tìm bit cao nhất
    if (x == 0 || y == 0)
        return 0;
    if (n <= 4)                         // nếu bit cao nhất <= 4 thì dùng built-in operator
        return x*y;
    
    n += n&1;                           // nếu n lẻ thì cho n += 1, nếu không thì n += 0
    int m = n >> 1;

    long long xl = x >> m;
    long long xr = x & ((1LL << m) - 1);
    long long yl = y >> m;
    long long yr = y & ((1LL << m) - 1);

    long long ll = mul(xl, yl);    // tính xl*yl
    long long rr = mul(xr, yr);    // tính xr*yr
    long long lr = mul(xl + xr, yl + yr) - (ll + rr);  // tính xl*yr + xr*yl

    long long ans = (ll << n) + (lr << m) + rr;
    return ans;
}

int main() {
    fstream fin("input_1.txt", ios::in);
    long long x, y;
    fin >> x >> y;

    cout << mul(x, y);
}