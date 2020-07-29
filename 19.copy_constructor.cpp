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

class A {
public :
    A() {
        cout << "class A constructor" << endl;
        this->x = 0x01020304;
    }
    A(const A &a) {
        this->x = a.x;
        cout << "class A copy constructor : " << this << endl; //对象的内存排布，对象的头部存储着父类的数据，因为这样可以使对象的起始地址不用变
    }
    int x;
};

class B : public A { //继承的语义，猫（子类）是动物（父类）即B是A，所以能把B类的对象，当参数传给类A的复制构造函数。
public :
    B() {
        this->y = 0x05060708;
        cout << "class B constructor" << endl;
    }
    B(const B &b) : A(b) { //继承下的构造，我们一定要显式性(使用默认的初始化列表会出现拷贝不完全的情况)的调用基类的拷贝构造，才能完成全部拷贝；一个对象可以绑定在其父类的引用上。
        this->y = b.y;
        cout << "class B copy constructor : " << this << endl;
    }
    int y;
};

int main() {
    B b1;
    //b1.x = 12, b1.y = 14;
    B b2(b1);
    cout << b2.x << " " << b2.y << endl;
    const char *msg = (const char *)(&b1); //int &b1 引用； 此处为取地址符
    for (int i = 0; i < sizeof(B); i++) {
        printf("%X", msg[i]); //地位放在地位，小端机
    }
    printf("\n");
    return 0;
}
