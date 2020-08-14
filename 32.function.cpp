#include <iostream>
#include <functional>

using namespace std;
//如何传递【任意可调用对象】作为参数？ 函数和函数对象都被称为可调用对象


namespace haizei {

template<typename RT, typename ...PARAMS> 
class base {
public:
    virtual RT operator()(PARAMS...) = 0;
    virtual base<RT, PARAMS...>*getCopy() = 0; //解决深拷贝时，对象类型丢失的问题
    virtual ~base() {}
};

template<typename RT, typename ...PARAMS> 
class normal_func : public base<RT, PARAMS...> {
public:
    typedef RT (*func_type)(PARAMS...);
    normal_func(func_type func) : ptr(func) {}
    virtual RT operator()(PARAMS... args) override {
        return this->ptr(args...);
    }
    virtual base<RT, PARAMS...> *getCopy() override {
    return new normal_func<RT, PARAMS...>(ptr);
    }
private:
    func_type ptr;
};

template<typename C, typename RT, typename ...PARAMS>  //typename C 推导函数对象的类型
class functor : public base<RT, PARAMS...> {
public:
    functor(C &func) : ptr(func) {}
    virtual RT operator()(PARAMS... args) override {
        return this->ptr(args...);
    }
    virtual base<RT, PARAMS...>*getCopy()override {
        return new functor<C, RT, PARAMS...>(ptr);
    }

private:
    C &ptr;
};




template<typename RT, typename ...PARAMS> class function;
template<typename RT, typename ...PARAMS>
class function<RT (PARAMS...)> {
    typedef normal_func<RT, PARAMS...> T1;
public:
    function(RT (*func)(PARAMS...)) //传入普通函数的构造函数 
    : ptr(new normal_func<RT, PARAMS...>(func)) {}
    
    template<typename T> //传入函数对象的构造函数
    function(T a) 
    : ptr(new functor <typename remove_reference<T>::type, RT, PARAMS...>(a)) {}
    
    //copy_constructor
    function(const function &f) {
       this->ptr = f.ptr->getCopy(); //因为我们无法确定后面需要拷贝的类型，所以只能让子类自己进行深拷贝（反着来）
    }
    //move_constructor
    function(function &&f) {
        this->ptr = f.ptr;
        f.ptr = nullptr;
    }

    RT operator()(PARAMS... args) {
        return this->ptr->operator()(args...);
    }
    ~function() {
        if (ptr != nullptr) delete ptr;
    }

private:
    base<RT, PARAMS...> *ptr; //步骤2、把函数或函数对象打包成一个新的函数对象（即base类，为了记录数据），然后把这个新的函数对象地址存储下来。
    };

} // end of haizei

void f(function<int(int, int)> g) { //返回值为int，传入参数两个int, g为对象名；步骤1、g对象（的赋值）可以接收普通函数和函数对象，然后调用构造函数。
    cout << g(3, 4) << endl;
    return ;
}

int add(int a, int b) {
    return a + b;
}

template <typename T, typename ...ARGS> class Add;
template <typename T, typename ...ARGS>
class Add<T(ARGS...)> {
public:
    T operator()(ARGS... args) {
        return add<T>(args...);
    }
private:
    template<typename T1, typename U, typename ...REST>
        T1 add(U a, REST... args) {
            return a + add<T1>(args...);
        }
    template<typename T1, typename U>
        T1 add(U a) {
            return a;
        }
};


struct MaxClass {
    int operator()(int a, int b) {
        return a > b ? a : b;
    }
};

/*class FunctionCnt {
public :
    FunctionCnt(function<int(int, int)> g) : g(g), __cnt(0) {}
    int operator()(int a, int b) {
        __cnt += 1;
        return g(a, b);
    }
    int cnt() { return __cnt; }
private:
    function<int(int, int)> g;
    int __cnt;
};*/

template<typename RT, typename ...ARGS> class FunctionCnt;
template<typename RT, typename ...ARGS>
class FunctionCnt<RT(ARGS...)> {
public :
    FunctionCnt(haizei::function<RT(ARGS...)> g) : g(g), __cnt(0) {} //function<RT(ARGS...)> g : (g)，第一个g为haizei::function 创建的对象g，g(g) 把haizei::function创建的g，传入到系统function的构造函数，因为有额外的存储空间，应该调用深拷贝，而我们未写深拷贝，调用系统默认的浅拷贝，haizei::function对象g是一个临时变量，被析构后，系统函数g指向一个被析构的对象
    RT operator()(ARGS... args) {
        __cnt += 1;
        return g(args...);
    }
    int cnt() { return __cnt; }
private:
    haizei::function<RT(ARGS...)> g; //系统function对象g
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
    
    FunctionCnt<int(int, int)>  add_cnt(add);
    cout << add_cnt(3, 4) << endl;;
    add_cnt(2, 4);
    add_cnt(4, 4);
    cout << add_cnt.cnt() << endl;

    Add<double(int, double)> add_plus;
    FunctionCnt<double(int, double)> add_test(add_plus);
    cout << add_test(11, 2.2) << endl;
    Add<string(string, string)> add_plus1;
    FunctionCnt<string(string, string)> add_test1(add_plus1);
    cout << add_test1("hello", " world!") << endl;
    return 0;
}

