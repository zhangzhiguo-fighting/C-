#include <iostream>
#include <functional>
using namespace std;

int mul(int a, int b) {
    return a * b;
}

int add(int a, int b) {
    return a + b;
}

int main() {
    int n = 10000, m, x, y;
    auto a = [&](int a, int b) {return a + b + n;}; // 每个lambda表达式的返回值都不一样,lambda表达式很想匿名函数，赋值语句记得加 ;
    n = 1000000;
    auto b = [&n](int a, int b) {return a + b + n;}; // []是一个口袋，可以装入外部的变量（闭包性质）
    /*auto c = [](int a, int b)->double {
        if (rand() % 2) {
            return c; //一个lambda表达式中不能出现两种类型的返回值，编译器将无法自动推导（auto）
        } else {
            return a + b;
        }
    };*/
    auto d = [](function<int(int, int)> a, function<int(int, int)> b) {
        return [=](int x) {
            return a(x, x) + b(x, x);
        };
    };
    cout << typeid(a).name() << endl;
    cout << typeid(b).name() << endl;
    cout << a(123, 456) << endl;
    cout << b(987, 120) << endl;
    auto e = d(a, b);
    auto f = d(mul, add);
    cout << e(12) << endl;
    cout << f(12) << endl;
    return 0;
}

