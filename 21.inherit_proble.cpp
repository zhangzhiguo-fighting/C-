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

struct A { 
    int x; 
};

struct B : virtual public A { //虚拟继承，合并有可能产生冗余的父类，但是子类对象的内存变大了（实部叠加，虚部整合）；如果不虚拟继承，D类中set和get方法访问的不是同一片存储区，去除的数据并不是所需要的
    void set(int x) {
        this->x = x;
        cout << "set : " << &this->x << endl;
    }
};

struct C : virtual public A {
    int get() { 
        cout << "get : " << &this->x << endl;
        return this->x;
    }
};

struct D : public B, public C {}; //菱形继承

int main() {
    D d;
    cout << sizeof(d) << endl; //正常继承大小为8字节（A类4字节，B类字节），虚拟继承24继承
    d.set(9973);
    cout << d.get() << endl;
    return 0;
}
