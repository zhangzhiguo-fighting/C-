#include <iostream>
using namespace std;

#define TEST(a, f) { \
    cout << #a <<  " : " << #f << " "; \
    f(a); \
}

void f2(int &x) {
    cout << "left value" << endl;
}

void f2(int &&x) {
    cout << "right value" << endl;
}

void f(int &x) {
    cout << "left value" << endl;
    TEST(x, f2);
}

void f(int &&x) {
    cout << "right value" << endl; //move函数强制变成右值，
    TEST(move(x), f2); //此处x是左值，f2检测目前的x是左值还是右值
    TEST(forward<int &&>(x), f2); //向下传递的时候，告诉下面是该什么引用
}


int test_func(const int &x) { //右值绑定在左值上，当左值是常量左值引用时。
    cout << x << endl;  //一个左值不能绑定在右值引用（或常量右值引用）上，因为右值使用后会被销毁（临时的变量）
    return 0;
}

int test_func1(const int &&x) {
    cout << x << endl;
    return 0;
}

int main() {
    int a, b = 1, c = 3;
    (++a) = b + c;
    cout << a << endl;
    a = 123 + 345; //左值：同样的变量，单一的方式（一个变量符号）访问到同样的结果
    (a++); //右值
    (++a); //左值
    (a = b) = c;
    cout << a << " " << b << endl;
    //int a[10];
    //a[3] = 12;
    TEST(a += 3, f);
    TEST(1 + 4, f);
    TEST(b + c, f);
    TEST(a++, f);
    TEST(++a, f);
    test_func(123); //右值
    test_func1(move(a));
    return 0;
}

