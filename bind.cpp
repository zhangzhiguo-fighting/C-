#include <iostream>
#include <functional>
using namespace std;

void func(int x, int y, int z) {
    cout << x + y << " is a number" << endl;
    cout << z << " is a number" << endl;
}

struct A {
    void say() {
        cout << this << " : saying" << endl;
    }
    void run() {
        cout << "hello world" << endl;
    }
};

void count_function_times(function<void()> &p, int &cnt) {
    p(); //调用a对象的run方法
    cnt += 1;
    return ;
}

int main() {
    function<void(int, int)> f1 = bind(func, 123, std::placeholders::_2, std::placeholders::_1); //注意placeholders_数字  的用法，y对应 placeholders_2, placeholders_2 对应 456
    f1(100, 456);
    f1(200, 789);
    A a;
    cout << &a << endl;
    function<void()> f2 = bind(&A::say, ref(a)); //ref() 告诉编译器传a的引用过去，而不是正常的复制一份然后再传送复制体的过去
    f2();
    //如何计算一个函数被调用的次数？
    int cnt = 0;
    function<void()> f3 = bind(&A::run, ref(a)); //把对象a的run方法绑定到f3上
    function<void()> f4 = bind(count_function_times, ref(f3), ref(cnt)); //bind让函数能当做参数在函数之间传递
    for (int i = 0; i < rand() % 10; i++) f4();
    cout << cnt << endl;
    return 0;
}

