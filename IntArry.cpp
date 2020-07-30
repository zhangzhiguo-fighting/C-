#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <vector>
#include <map>
#include <cmath>
#include <queue>
#include <ctime>
using namespace std;

class IntArray {
public :
    IntArray(int n) : n(n) {
        this->arr = new int[n];
    }
    IntArray(const IntArray &obj) : n(obj.n) {
        this->arr = new int[n];
        for (int i = 0; i < n; i++) {
            this->arr[i] = obj.arr[i];
        }
    }
    int &operator[](int ind) {
        if (ind >= 0) {
            return this->arr[ind];
        }
        return this->arr[n + ind];
    }
    void operator+=(int x) { //此处函数返回类型不重要，所以我们选择返回void类型
        for (int i = 0; i < n; i++) {
            this->arr[i] += x;
        }
        return ;
    }
    IntArray &operator++() { //前++，返回的是调用对象本身的引用，也就是它本身
        for (int i = 0; i < n; i++) {
            this->arr[i] += 1;
        }
        return *this;
    }
    IntArray operator++(int x) { //后++，返回的是另一个对象，记录++前的对象然后返回，参数int区分前++和后++
        IntArray ret = (*this);
        for (int i = 0; i < n; i++) {
            this->arr[i] += 1;
        }
        return ret;
    }
    ~IntArray() {
        delete[] this->arr;
    }
    friend ostream &operator<<(ostream &, const IntArray &);
private :
    int *arr, n; //记录传入的长度
};

ostream &operator<<(ostream &out, const IntArray &a) {
    out << "<Class IntArray> : ";
    for (int i = 0; i < a.n; i++) {
        out << a.arr[i] << " ";
    }
    return out;
}

int main() {
    srand(time(0));
    IntArray a(10);
    for (int i = 0; i < 10; i++) {
        a[i] = rand() % 100;
    }
    cout << a[4] << endl;
    cout << a[-2] << endl; // 输出倒数第 2 位的值
    cout << a << endl; // 输出整个数组中的元素
    a += 5; // 给数组中所有元素都加5
    cout << a << endl; // 输出整个数组中的元素
    cout << (a++) << endl; // 给数组中的所有元素都加 1
    cout << (++a) << endl; // 给数组中的所有元素都加 1
    return 0;
}
