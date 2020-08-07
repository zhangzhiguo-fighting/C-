#include <iostream>
using namespace std;

constexpr int f(int x) { //返回一个编译器常量，且函数也可以继续当成正常函数来使用；C++11不支持递归函数做成编译期变量（不能修饰递归函数）
    return 3 * x * x + x;
}

class A {
public:
    constexpr A(int x, int y) : x(x), y(y) {}
    int x, y;

private:

};

int main() {
    int n;
    cin >> n;
    constexpr int m = f(12); 
    //constexpr int m = 2 * 12; //12 换成 n ，我们通常把 const 当做运行期变量；constexpr作为编译器常量，只有编译器变量可以给编译器变量赋值
    cout << m << endl;
    //const int n = 123;
    //cout << n << endl;
    constexpr A a(2, 3); //编译器常量在初始化的时候，要求整个过程都是编译期常量。
    cout << a.x << ", " << a.y << endl;
    return 0;
}

