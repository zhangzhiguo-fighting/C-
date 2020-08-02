#include <iostream>
using namespace std;

class A {
public:
    virtual ~A() {} //实现多态
private:
};

class B : public A {
public:
    void sayB() {
        cout << "this is class B, x = " << x << endl;
    }
    int x;
};
class C : public A {
public:
    void sayC() {
        cout << "this is class C, x = " << x << endl;
    }
    double x;
};
class D : public A {
public:
    void sayD() {
        cout << "this is class D, x = " << x << endl;
    }
    string x;
};


int my_dynamic_cast(A *ta) {
    char **pa = (char **)(ta); //存储指针的一片连续的空间
    char **pb = (char **)new B();
    char **pc = (char **)new C();
    char **pd = (char **)new D();
    int ret = -1;
    if (pa[0] == pb[0]) ret = 0;
    else if (pa[0] == pc[0]) ret = 1;
    else if (pa[0] == pd[0]) ret = 2;
    return ret;
}

int main() {
    srand(time(0));
    A *pa;
    B *pb;
    C *pc;
    D *pd;
    switch (rand() % 3) {
        case 0: pb = new B(); pa = pb; pb->x = 123; break;
        case 1: pc = new C(); pa = pc; pc->x = 45.6; break;
        case 2: pd = new D(); pa = pd; pd->x = "hello haizei"; break;
    }
    //dynamic_cast 父类的地址向子类地址的转换，如果类型不匹配，会返回一个空指针
    if ((pb = dynamic_cast<B *>(pa))) { //为什么要要求多态的才能使用 dynamic_cast 比较头部的指向虚函数表的指针
        cout << "Class B : ";
        pb->sayB();
    } else if (pc == (dynamic_cast<C *>(pa))) {
        cout << "Class C : ";
        pc->sayC();
    } else if (pd == (dynamic_cast<D *>(pa))) {
        cout << "Class D : ";
        pd->sayD();
    }

    switch (my_dynamic_cast(pa)) {
    case 0: ((B *)(pa))->sayB(); break;
    case 1: ((C *)(pa))->sayC(); break;
    case 2: ((D *)(pa))->sayD(); break;
    }

    return 0;
}
