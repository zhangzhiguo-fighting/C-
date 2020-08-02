#include <iostream>
#include <time.h>
using namespace std;

class Animal {
public:
    virtual void run() {
        cout << "I don't konw how to run" << endl;
    }
};

class Cat : public Animal {
public:
    void run() {
        cout << "I can run with four legs" << endl;
    }
};
class Dog : public Animal {
public:
    void run() {
        cout << "I can run with four legs, tail yao a yao!" << endl;
    }
};
class Bat : public Animal {
public:
    void run() {
        cout << "I can fly!" << endl;
    }
};

class A {
public:
    A() = default;
    A(string s) {
        cout << " param constructor" << endl;
    }
    A(const A &a) {
        cout << "copy constructor" << endl;
    }
    int x;
    virtual void say(int xx) {
        cout << this << endl; //成员方法中的一个隐藏参数
        cout << "Class A : I can say, xx = " << xx << ", this->x = " << x << endl;
    }
};

typedef void (*func)(void *, int);

A retA() {
    A temp_a("hello world"); //在此，返回值优化，第一个参数可以传如temp_c的地址，让函数中的修改，全部直接作用在temp_c上。
    return temp_a;
}

class Base{
    public :
    Base() {
        cout << "Base constructor" << endl;
        this->x = new int;
    }
    virtual ~Base() { //拥有继承的父类中的析构函数一定要是虚函数
        cout << "Base destructor" << endl;
        delete this->x;
    }
    private:
    int *x;
};

class Base_A : public Base {
    public :
    Base_A() {
        cout << "Base_A constructor" << endl;
        this->y = new int;
    }
    ~Base_A() {
        cout << "Base_A destructor" << endl;
        delete this->y;
    }
    private:
    int *y;
};

int main() {
    Base *ba = new Base_A();
    delete ba; //析构函数为普通成员方法，ba为Base类，所以它只调用Base类的析构函数，子类不会被析构析构，出现内存泄露，所以父类析构函数必须为虚函数。

    cout << sizeof(A) << endl;
    
    A temp_a, temp_b;
    temp_a.x = 9973;
    temp_b.x = 10000;
    temp_a.say(67); //67未覆盖原temp_a.x中的9973
    
    //A temp_c = retA();
    ((func **)(&temp_a))[0][0](&temp_b, 6);
    srand(time(0));
    Cat a;
    //Animal &b = a;
    Animal *c[10];
    cout << sizeof(a) << endl;
    for (int i = 0; i < 10; i++) {
        int op = rand() % 3;
        switch (op) {
            case 0: c[i] = new Cat(); break;
            case 1: c[i] = new Dog(); break;
            case 2: c[i] = new Bat(); break;
        }
    }
    for (int i = 0; i < 10; i++) {
        c[i]->run();
    }
    return 0;
}

