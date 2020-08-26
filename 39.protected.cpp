#include <iostream>
using namespace std;

class A {
public:
    A() {
        x = rand() % 100;
        cout << this << "init x value : " << x << endl;
    }
protected:
    int x;
};

class C : public A {
public:
    int z;
};

class B : public A {
public:
    void say(B& b) {
        cout << &b << " x value : " << (static_cast<A&>(b).x) << endl;
    }
    void say(C& c) {
        cout << &b << " x value : " << (static_cast<A&>(c).x) << endl;
    }
};

int main() {
    B b1, b2;
    b1.say(b2);
    return 0;
}

