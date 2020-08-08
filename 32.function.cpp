#include <iostream>
#include <functional>

using namespace std;
//如何传递【任意可调用对象】作为参数？ 函数和函数对象都被称为可调用对象


namespace haizei {

template<typename RT, typename ...PARAMS> 
class base {
public:
    virtual RT operator()(PARAMS...) = 0;
    virtual ~base() {}
};

template<typename RT, typename ...PARAMS> 
class normal_func : public base<RT, PARAMS...> {
public:
    typedef RT(*func_type)(PARAMS...);
    normal_func(func_type func) : ptr(func) {}
    virtual RT operator()(PARAMS... args) override {
        return this->ptr(args...);
    }
private:
    func_type ptr;
};

template<typename C, typename RT, typename ...PARAMS>
class functor : public base<RT, PARAMS...> {
public:
    functor(C &func) : ptr(func) {}
    virtual RT operator()(PARAMS... args) override {
        return this->ptr(args...);
    }
private:
    C &ptr;
};




template<typename RT, typename ...PARAMS> class function;
template<typename RT, typename ...PARAMS>
class function<RT (PARAMS...)> {
public:
    function(RT (*func)(PARAMS...)) //传入普通函数的构造函数 
    : ptr(new normal_func<RT, PARAMS...>(func)) {}
    
    template<typename T> //传入函数对象的构造函数
    function(T &&a) 
    : ptr(new functor <typename remove_reference<T>::type, RT, PARAMS...>(a)) {}

    RT operator()(PARAMS... args) {
        return this->ptr->operator()(args...);
    }
    ~function() {
        delete ptr;
    }

private:
    base<RT, PARAMS...> *ptr; //步骤2、把函数和函数对象打包成一个新的函数对象（即base类，为了记录数据），然后把这个新的函数对象地址存储下来。
};

} // end of haizei

void f(function<int(int, int)> g) { //返回值为int，传入参数两个int, g为对象名；步骤1、g对象（的赋值）可以接收普通函数和函数对象，然后调用构造函数。
    cout << g(3, 4) << endl;
    return ;
}

int add(int a, int b) {
    return a + b;
}

struct MaxClass {
    int operator()(int a, int b) {
        return a > b ? a : b;
    }
};

class FunctionCnt {
public :
    FunctionCnt(function<int(int, int)> g) : g(g) {}
    int operator()(int a, int b) {
        __cnt += 1;
        return g(a, b);
    }
    int cnt() { return __cnt; }
private:
    function<int(int, int)> g;
    int __cnt;
};

int main() {
    MaxClass max;
    f(add);
    f(max);
    haizei::function<int(int, int)>g1(add);
    haizei::function<int(int, int)>g2(max);
    cout << g1(3, 4) << endl;
    cout << g2(3, 4) << endl;
    
    FunctionCnt add_cnt(add);
    add_cnt(3, 4);
    add_cnt(2, 4);
    add_cnt(4, 4);
    cout << add_cnt.cnt() << endl;
    return 0;
}

