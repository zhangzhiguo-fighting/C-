#include <iostream>
using namespace std;

struct A {
public:
    int x;
};

struct B : public A {
public :
    int y;
};

int main() {
    A *arr = new B()[10]; //A 和 B 的sizeof不一样大；这个用法只能指向单一对象
    arr[0];
    arr[1];
    arr[2];
    return 0;
}

