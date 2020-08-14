#include <iostream>
#include <functional>
using namespace std;

int add(int a, int b) {
    cout << a << " + " << b << " = " << a + b << endl;
    return a + b;
}
 
int add2(int a, int b, int c) {
    cout << a << " " << b << " " << c << endl;
    return a + b + c;
}

int add_cnt(function<int(int, int)> func, int &n, int a, int b) {
    n += 1;
    return func(a, b);
}

int main() {
    function<int(int)> f1 = bind(add, 5, placeholders::_1);
    f1(3), f1(4), f1(5);
    function<int(int, int)> f2 = bind(add, placeholders::_2, placeholders::_1);
    f2(3, 4), f2(5, 6), f2(7, 8);
    
    function<int(int, int)> f3 = bind(add2, placeholders::_2, 6, placeholders::_1);
    f3(9, 10);
    function<int(int, int, int)> f4 = bind(add2, placeholders::_1, placeholders::_3 , placeholders::_2); //将一种传参变成另一种传参
    f4(1, 2, 3);    

    //绑定一个统计函数执行次数的方法
    int n = 0;
    function<int(int, int)> f5 = bind(add_cnt, add, ref(n), placeholders::_1, placeholders::_2); //bind也是一个模板，当直接传 n 过去，n是一个值，T会被推导类型，而不是引用，n会被拷贝一份传过去绑定，所以不使用ref()（告诉编译器传引用过去），n的最终值为0
    f5(99, 88);
    f5(21, 22);
    f5(55, 11);
    cout << n << endl;
    return 0;
}

