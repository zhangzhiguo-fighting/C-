#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <queue>
#include <stack>
#include <algorithm>
#include <string>
#include <map>
#include <set>
#include <vector>
using namespace std;

class People {
    friend int main(); //隔壁老王
    int x, y; //默认成员是私有的，访问控制权限是针对类外来说  
public :
    void set(int x);
    void say();
};

struct People2 { //C++ 底层用class实现了struct（保留语法，向下兼容）
    int x, y; // struct 也是类，但是它的成员默认为public
};

void People::set(int x) {
    cout << "set function : " << this << endl;
    this->x = x; //谁调用set函数，this指针就只想该对象
    return ;
}

void People::say() {
    cout << x << " " << y << endl;
    return ;
}

int main() {
    People a;
    People2 b;
    a.y = 18432;
    cout << "a object : " << &a << endl;
    a.set(3);
    b.x = 4;
    a.say();
    cout << b.x << endl;
    return 0;
}
