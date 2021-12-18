#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

struct node {
    int data;
    node* next;

    node(int _dat) : data(_dat) {}
};

// bài toán Josephus, dùng linked list vòng
void printJosephus(int n) {
    node* iter = new node(1);
    node* start = iter;
    for(int i = 2; i <= n; i++) {
        iter->next = new node(i);
        iter = iter->next;
    }
    iter->next = start;
    iter = start;

    while(iter->next != iter) {
        node* tmp = iter->next;
        cout << tmp->data << " ";
        iter->next = tmp->next;
        iter = iter->next;
        delete tmp;
    }
    cout << "\n" << iter->data;
}

int main() {
    fstream fin("input_2.txt", ios::in);
    int n;
    fin >> n;

    printJosephus(n);
}