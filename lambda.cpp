#include <iostream>
#include<cmath>
#include <functional>
using namespace std;

auto add = [] (int a, int b) -> long long { //lambda表示式以[]开头，它是一个赋值语句所以后面需要加上;
    return a + b; // 返回值类型也是lambda自己推导，lambda表达式类似函数，它每次执行只能返回一个类型的返回值。可以使用返回值后置来制定返回值类型
};

auto Data = [](int a, int b) { // 传入a, b然后把a,b 【打包】 到一个lambda表达式，然后在返回一个lambda表达式
    return [=] (auto func) { // =值捕获
        return func(a, b); // 里面的a,b不能捕获外面a,b的值，要捕获（拷贝），需要使用 = 值捕获
    };
};

auto First = [](int a, int b) {
    return a;
};

auto Second = [](int a, int b) {
    return b;
};

auto Add = [](int a, int b) {
    return a + b;
};

auto Max = [](int a, int b) {
    return max(a, b);
};

function<int()> Temp_Func() {
    int a= 23;
    return [=]()->int {
        return a;
    };
}

int main() {
    cout << add(2, 4) << endl;
    auto func = Temp_Func();
    cout << func() << endl;
    auto a = Data(rand() % 1000, rand() % 1000); //a lambda对象可以接受一个lambda表达式（类似构造函数）
    cout << a(First) << endl; //操作被当成参数传入
    cout << a(Second) << endl;
    cout << a(Add) << endl;
    cout << a(Max) << endl;
    return 0;
}

