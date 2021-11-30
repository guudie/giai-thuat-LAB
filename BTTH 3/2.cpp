#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <math.h>
using namespace std;

int** matCopy(int** a, int n, int row, int col) {
    int** c = new int*[n];
    for(int i = 0; i < n; i++) {
        c[i] = new int[n];
        for(int j = 0; j < n; j++)
            c[i][j] = a[row+i][col+j];
    }

    return c;
}

int** matAdd(int** a, int** b, int n, int sign = 1) {
    int** c = new int*[n];
    for(int i = 0; i < n; i++) {
        c[i] = new int[n];
        for(int j = 0; j < n; j++)
            c[i][j] = a[i][j] + sign*b[i][j];
    }

    return c;
}

void matAdd(int** a, int** b, int** c, int n, int sign = 1) {
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            c[i][j] = a[i][j] + sign*b[i][j];
}

void matMul(int** a, int** b, int** c, int n) {
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            c[i][j] = 0;
            for(int k = 0; k < n; k++)
                c[i][j] += a[i][k]*b[k][j];
        }
    }
}

void join(int** c11, int** c12, int** c21, int** c22, int** c, int n) {
    for(int i = 0; i < n/2; i++)
        for(int j = 0; j < n/2; j++) {
            c[i][j] = c11[i][j];
            c[i][j+n/2] = c12[i][j];
            c[i+n/2][j] = c21[i][j];
            c[i+n/2][j+n/2] = c22[i][j];
        }
}

void strassen(int** a, int** b, int** c, int n) {
    if(n <= 2)
        matMul(a, b, c, n);
    else {
        // khai báo các ma trận cần thiết cho tính toán
        // chia ma trận a thành 4 phần
        int** a11 = matCopy(a, n/2, 0, 0);                          
        int** a12 = matCopy(a, n/2, 0, n/2);                        
        int** a21 = matCopy(a, n/2, n/2, 0);                        
        int** a22 = matCopy(a, n/2, n/2, n/2);                      

        // chia ma trận b thành 4 phần
        int** b11 = matCopy(b, n/2, 0, 0);                          
        int** b12 = matCopy(b, n/2, 0, n/2);                        
        int** b21 = matCopy(b, n/2, n/2, 0);                        
        int** b22 = matCopy(b, n/2, n/2, n/2);                      

        int** a11_22 = matAdd(a11, a22, n/2);               // a11 + a22
        int** a21_22 = matAdd(a21, a22, n/2);               // a21 + a22
        int** a11_12 = matAdd(a11, a12, n/2);               // a11 + a12
        int** a21_11 = matAdd(a21, a11, n/2, -1);           // a21 - a11
        int** a12_22 = matAdd(a12, a22, n/2, -1);           // a12 - a22

        int** b11_22 = matAdd(b11, b22, n/2);               // b11 + b22
        int** b21_22 = matAdd(b21, b22, n/2);               // b21 + b22
        int** b11_12 = matAdd(b11, b12, n/2);               // b11 + b12
        int** b21_11 = matAdd(b21, b11, n/2, -1);           // b21 - b11
        int** b12_22 = matAdd(b12, b22, n/2, -1);           // b12 - b22

        int** m1 = new int*[n/2];
        int** m2 = new int*[n/2];
        int** m3 = new int*[n/2];
        int** m4 = new int*[n/2];
        int** m5 = new int*[n/2];
        int** m6 = new int*[n/2];
        int** m7 = new int*[n/2];
        for(int i = 0; i < n/2; i++) {
            m1[i] = new int[n/2];
            m2[i] = new int[n/2];
            m3[i] = new int[n/2];
            m4[i] = new int[n/2];
            m5[i] = new int[n/2];
            m6[i] = new int[n/2];
            m7[i] = new int[n/2];
        }

        // tính các m_i
        strassen(a11_22, b11_22, m1, n/2);
        strassen(a21_22, b11, m2, n/2);
        strassen(a11, b12_22, m3, n/2);
        strassen(a22, b21_11, m4, n/2);
        strassen(a11_12, b22, m5, n/2);
        strassen(a21_11, b11_12, m6, n/2);
        strassen(a12_22, b21_22, m7, n/2);

        int** c11 = new int*[n/2];                  
        int** c12 = new int*[n/2];                  
        int** c21 = new int*[n/2];                  
        int** c22 = new int*[n/2];                  
        for(int i = 0; i < n/2; i++) {
            c11[i] = new int[n/2];
            c12[i] = new int[n/2];
            c21[i] = new int[n/2];
            c22[i] = new int[n/2];
        }

        // tính c11, c12, c21, c22
        matAdd(m1, m4, c11, n/2);  matAdd(c11, m5, c11, n/2, -1);  matAdd(c11, m7, c11, n/2);       // c11 = m1 + m4 - m5 + m7
        matAdd(m3, m5, c12, n/2);       // c12 = m3 + m5
        matAdd(m2, m4, c21, n/2);       // c21 = m2 + m4
        matAdd(m1, m3, c22, n/2);  matAdd(c22, m2, c22, n/2, -1);  matAdd(c22, m6, c22, n/2);       // c22 = m1 + m3 - m2 + m6
        join(c11, c12, c21, c22, c, n);


        // giải phóng bộ nhớ
        // for(int i = 0; i < n/2; i++)
        //     delete[] ...[i];
        // delete[] ...;
    }
}

void print(int** a, int n) {
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++)
            cout << a[i][j] << "\t";
        cout << "\n";
    }
}

int main() {
    fstream fin("input_2.txt", ios::in);
    int n, m;
    fin >> n;
    m = 1 << (int)log2(n);
    if(m < n)
        m = m << 1;
    
    int** a = new int*[m];
    int** b = new int*[m];
    int** c = new int*[m];

    for(int i = 0; i < m; i++) {
        a[i] = new int[m];
        b[i] = new int[m];
        c[i] = new int[m];
        for(int j = 0; j < m; j++)
            a[i][j] = b[i][j] = c[i][j] = 0;
    }

    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            fin >> a[i][j];
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            fin >> b[i][j];
    
    strassen(a, b, c, m);
    print(c, n);
}