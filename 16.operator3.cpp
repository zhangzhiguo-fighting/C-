#include <iostream>
using namespace std;
//对象开辟的空间都是为了存储成员属性和成员方法
/*内部实现*/
class A {
public:
    A() {
        arr = new int[10];
    }
    A(const A &a) : A() {
        for (int i = 0; i < 10; i++) {
            this->arr[i] = a.arr[i];
        }
        this->x = a.x;
        this->y = a.y;
    }
    int x, y;
    int *arr;
};

class B {
public:
    B() : obj(nullptr){
        arr = new int[10];
        arr[3] = 9973;
    }
    B(A *obj) : B() { //调用无参的构造函数
        this->obj = obj;
    }
    int operator()(int a, int b) {
        return a + b;
    }
    int &operator[](int ind) {
        return arr[ind];
    }
    void operator[](const char *msg) {
        cout << msg << endl;
        return ;
    }

    A *operator->() {
        return obj;
    }
    A &operator*() {
        return *obj;
    }

    ~B() {
        delete arr;
    }
private:
    int *arr;
    A *obj;
};

ostream &operator<<(ostream &out, const A &a) {
    cout << "A(" << a.x << ", " << a.y << ")";
    return out;
}

/*外部表现*/
int main() {
    B add;
    cout << add(3, 4) << endl; //函数对象，通过重载()运算符实现的
    cout << add[3] << endl; //数组对象，重载[]类似数组
    add[3] = 8876; //如果[]返回int类型就会出错，因为=左边不是变量
    cout << add[3] << endl;
    add["hello world"];
    
    //指针对象,表现像指针
    A a, b(a);
    a.x = 67, a.y = 99;
    B p = &a; //此处&是取地址符
    cout << p->x << " " << p->y << endl; //->单目运算符，后面的符号就是一个标示符
    cout << *p << endl;

    //深浅拷贝
    a.arr[3] = 9976;
    b.arr[3] = 6685;
    cout << a.arr[3] << endl;
    cout << b.arr[3] << endl;
    cout << sizeof(A) << endl;
    return 0;
}

