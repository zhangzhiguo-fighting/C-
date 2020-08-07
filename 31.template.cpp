#include <iostream>
using namespace std;

namespace haizei {

class A {
public:
    A(int x) :x(x) {}
    int x;
};

class B {
public:
    B(int y) : y(y) {}
    int y;
};

int operator+(const A &a, const B &b) {
    return a.x + b.y;
}

template<typename T, typename U> //typename, class　作用上没有任何区别
auto add(T a, U b) -> decltype(a + b) { //decltype() 用来推导表达式返回值的类型，返回值后置
    return a + b;
}

template<> //函数模板的特化形式
int add(int a, int b) {
    cout << "add int : " << a << " " << b << endl;
    return a + b;
}

template<typename T, typename U> //模板的片特化
auto add(T *a, U *b) -> decltype(*a + *b) {
    return add(*a, *b); //二维地址也行，递归调用两次add(*a, *b)
}

template<typename T, typename U>
auto max(T a, U b) -> decltype(a > b ? a : b) { //不能重载三目运算符 decltype(a + b)
    return a > b ? a : b;
}
template<typename T, typename U>
auto min(T a, U b) -> decltype(a > b ? b : a) {
    return a > b ? b : a; //工具类设计思想，尽量使用同一个符号，可以让自定义类型少重载符号。
}

class PrintAny { //一个拥有模板方法的类
public:
    template<typename T>
        void operator()(const T &a) {
            cout << a << endl;
        }
};

template<typename T>
class FoolPrintAny {
public: 
    void operator()(const T &a) {
        cout << a << endl;
    }
};

template<>
class FoolPrintAny<int> {
public:
    void operator()(const int &a) {
        cout << "naughty : " << 2 * a << endl;
    }
};


template<typename  T> //使用特化模板，解决递归一直展开的问题
void printAny(const T &a) {
    cout << a << endl;
    return ;
}

template<typename T, typename ...ARGS> //变参模板
void printAny(const T &a, ARGS... args) {
    cout << a << " ";
    printAny(args...);
    return ;
}

//帮助模板类展开的模板类
template<typename T, typename ...ARGS>
struct ARG {
    typedef T __type;
    typedef ARG<ARGS...> __rest;
};

template<typename T>
struct ARG<T> {
    typedef T __type;
};


template<typename T, typename ...ARGS> class Test; //工具模板类，去解析变参列表
template<typename T, typename ...ARGS>
class Test<T(ARGS...)> { //使用偏特化形式，让这个模板类使用更像一个函数
public:
    T operator()(
        typename ARG<ARGS...>::__type a, 
        typename ARG<ARGS...>::__rest::__type b) {
        return a + b;
    }
};


}

int main() {
    haizei::A a(1000);
    haizei::B b(645);
    cout << a + b << endl;
    cout << haizei::add(2, 3) << endl; //隐式的推导, 单一模板我们在使用的时候不光要知道声明，还要需要知道模板的定义（模板的定义实现在头文件中），根据模板定义在编译时生成具体逻辑函数
    cout << haizei::add(2.3, 4.5) << endl;
    //cout << add<double>(2.3, 3) << endl; //<>显示的实例化，调用的Ｔ为ｄｏｕｂｌｅ类型
    cout << haizei::add(2.3, 3.6) << endl;
    cout << haizei::add(string("hello"), "hello world") << endl;
    cout << haizei::add(a, b) << endl;
    cout << max(4, 3) << endl;
    cout << haizei::max(4.3, 3) << endl;
    cout << haizei::min(4.3, 3) << endl;
    haizei::PrintAny print; //有一个PrintAny的类
    print(123); //模板的实例化会生成具体的函数或类，模板的参数就是哪些未确定的类型，operator()(int); 当我们使用模板方法的时候，模板方法再进行实例化（把各个参数固定）
    print(34543);
    print(3.4);
    print("hello world");
    print("hello haizei");
    print(&a);
    haizei::FoolPrintAny<string> f;
    f(string("hello world"));
    haizei::FoolPrintAny<int> f2;
    f2(123);
    int n = 45, m = 67;
    int *p = &n, *q = &m;
    cout << haizei::add(n, m) << endl;
    cout << haizei::add(p, q) << endl;
    haizei::printAny(123, 34.5, "hello world", &a);
    haizei::Test<int(int, int)> f3; //函数对象
    cout << f3(3, 4) << endl;
    return 0;
}

