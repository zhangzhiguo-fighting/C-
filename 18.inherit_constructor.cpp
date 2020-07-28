#include <iostream>
using namespace std;

class D {
public:
    D() { cout << "D constructor" << endl; }
    ~D() {
        cout << "D destructor" << endl;
    }
};

class A {
public:
    A() = delete;
    A(int x, int y) {cout << "A constructor" << endl;}
    ~A() {
        cout << "A destructor" << endl;
    }
};

class B {
public:
    B() {cout << "B constructor" << endl;}
    ~B() {
        cout << "B destructor" << endl;
    }
};

class C : public D {
public:
    C() : a(3, 4) {cout << "C constructor" << endl; } //初始化列表不能决定初始化的顺序（按照声明对象），但会按初始化要求进行初始化，系统默认的初始化列表是分别调用父类的默认构造函数
    //没写b也会调用b的默认构造函数(初始化列表完成)

    ~C() {
        cout << "C destructor" << endl;
    } //析构时，先析构子类，再析构父类

private:
    //A a;
    B b; //B声明在A的前面，所以完成对象a构造前，会调用对象b的构造函数，又因为没给要求，所以默认初始化列表回去调用B默认的构造函数
    A a;
};


int main() {
    C c;
    return 0;
}

