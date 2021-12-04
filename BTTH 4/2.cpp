#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

struct node {
    int data;
    node* next;

    node(int _dat) : data(_dat) {}
};

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

    // vector<int> j;
    // for(int i = 1; i <= n; i++)
    //     j.push_back(i);
    
    // int i = 0;
    // while(j.size() > 1) {
    //     int nxt = (i+1)%j.size();
    //     cout << j[nxt] << " ";
    //     j.erase(j.begin()+nxt);
    //     if(nxt < i)
    //         i--;
    //     i = (i+1)%j.size();
    // }
    // cout << "\n" << j[0];
}

int main() {
    fstream fin("input_2.txt", ios::in);
    int n;
    fin >> n;

    printJosephus(n);
}