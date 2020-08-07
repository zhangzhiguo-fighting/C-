#include <iostream>
#include <map>
using namespace std;


class A : public map<int, int> {
public:
    virtual void say() {
        cout<< "Class A : hello world" << endl;
    }
};
class B final : public A { //作用二、防止当前的类被意外的继承
public:
    void say() final override { //作用一、防止子类对父类相关方法的重写覆盖
        cout<< "Class B : hello world" << endl;
    }
};

/*class C : public B {
public:
    void say() override {
        cout<< "Class C : hello world" << endl;
    }
};*/

int main() {
    A a;
    a[213] = 213;
    a[323] = 222;
    for (auto x : a) {
        cout << x.first << " " << x.second <<endl;
    }
    return 0;
}

