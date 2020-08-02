#include <iostream>
using namespace std;

class Animal {
public:
    Animal (const string &name) : __name(name) {}
    void run();
protected:
    string __name;
};

class Cat : public Animal {
public:
    Cat() : Animal("cat") {}
    void run() { //virtual
        cout << "I can run with four legs" << endl;
    }
};

int main() {
    Cat a;
    Animal &b = a; //Animal的引用b绑定在对象a上
    Animal *c = &a; //Animal的指正指向对象a
    
    //一下代码跑不通，要跑通的话，需要使用虚函数，所有虚函数都可以被子类所覆盖。
    a.run(); //让这只猫跑
    b.run(); //让这只动物跑
    c->run(); //让这只动物跑，当我们用指针去间接引用某个方法时，找的是指针（Animal类）里面是否有这个方法，Animal里面没实现run方法
    return 0;

}
