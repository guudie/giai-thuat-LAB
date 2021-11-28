#include <iostream>
#include <fstream>
using namespace std;

struct triplet {
    int a, b, c;
    friend ostream& operator<<(ostream& os, const triplet& other) {
        os << other.a << " " << other.b << " " << other.c;
        return os;
    }
};

triplet largestSum(int* const& arr, int l, int r) {
    if(l==r)
        return { arr[l], l, r };
    
    int m = (l+r)/2;
    triplet maxL = largestSum(arr, l, m);
    triplet maxR = largestSum(arr, m+1, r);

    if(maxL.a < 0)  maxL = {0, -1, -1};
    if(maxR.a < 0)  maxR = {0, -1, -1};
    
    triplet curMaxL = {0, -1, m};
    int tmp = 0;
    for(int i = m; i >= l; i--) {
        tmp += arr[i];
        if(tmp > curMaxL.a) {
            curMaxL.a = tmp;
            curMaxL.b = i;
        }
    }

    triplet curMaxR = {0, m+1, -1};
    tmp = 0;
    for(int i = m+1; i <= r; i++) {
        tmp += arr[i];
        if(tmp > curMaxR.a) {
            curMaxR.a = tmp;
            curMaxR.c = i;
        }
    }

    triplet ans({0, -1, -1});
    if(ans.a < maxL.a)                  ans = maxL;
    if(ans.a < maxR.a)                  ans = maxR;
    if(ans.a < curMaxL.a)               ans = curMaxL;
    if(ans.a < curMaxR.a)               ans = curMaxR;
    if(ans.a < curMaxL.a + curMaxR.a)   ans = {curMaxL.a+curMaxR.a, curMaxL.b, curMaxR.c};
    if(ans.b == -1 || ans.c == -1)      ans.b = ans.c = -1;

    return ans;
}

int main() {
    fstream fin("input_3.txt", ios::in);
    int n;
    fin >> n;
    int* arr = new int[n];
    for(int i = 0; i < n; i++)
        fin >> arr[i];
    
    triplet ans = largestSum(arr, 0, n-1);
    if(ans.b == -1)
        cout << "Day con tong lon nhat la tap rong!\n-1 -1\n0";
    else {
        for(int i = ans.b; i <= ans.c; i++)
            cout << arr[i] << " ";
        cout << "\n" << ans.b << " " << ans.c;
        cout << "\n" << ans.a;
    }
}