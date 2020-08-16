#include <iostream>
using namespace std;
//模板在编译期无法展开循环，但是可以展开递归

template<int n>
struct IsEven {
    static constexpr int r = !(n % 2);
};

template<int a, int b>
struct Add {
    static constexpr int r = a + b;
};

// 1 ~ n 求和
template<int n>
struct Sum {
    static constexpr int r = n + Sum<n - 1>::r; //算10扩展出11个类，空间换时间
};
template<> //递归出口
struct Sum<0> {
    static constexpr int r=  0;
};

// 求阶乘
template<int n>
struct Factorial {
    static constexpr int r = n * Factorial<n - 1>::r;
};
template<> //递归出口
struct Factorial<1> {
    static constexpr int r = 1;
};

//判断 n 的素数
template<int n, int i>
struct getNextN {
    static constexpr int r = (i * i > n ? 0 : n);
};

template<int n, int i>
struct getNextI {
    static constexpr int r = (n % i == 0 ? 0 : i + 1);
};

template<int n, int i> // 2
struct IsTest {
    //static constexpr int r = (n % i == 0 ? 0 : (i * i <= n ? IsTest<n, i + 1>::r : 1));
    static constexpr int r = IsTest<getNextN<n, i>::r, getNextI<n, i>::r> ::r;
};

template<int i> //偏特化版本
struct IsTest<0, i> {
    static constexpr int r = 1;
};

template<int n>
struct IsTest<n, 0> {
    static constexpr int r = 0;
};

template<int i>
struct IsTest<2, i> {
    static constexpr int r = 1;
};

template <int n> // 1
struct IsPrime {
    static constexpr int r = IsTest<n, 2>::r; 
};

/*bool is_prime(int i, int n) {
    if (i * i > n) return true;
    if (n % i == 0) return false;
    return is_prime(i + 1, n);
}*/

//素数求和
template <int n>
struct SumPrime {
    static constexpr int r = (n * IsPrime<n>::r) + SumPrime<n - 1>::r;
};
template<>
struct SumPrime<1> {
    static constexpr int r = 0;
};

//打印出素数
template <int n, int i>
struct Print {
    static constexpr void print() {
        if (IsPrime<i>::r) cout << i << " ";
        Print<n, i + 1>::print();
    } 
};

template<int n>
struct Print<n, n> {
    static constexpr void print() {
        //if (IsPrime<n>::r) cout << n << " ";
        return ;
    }
};

template <int n>
struct PrintPrime {
    static constexpr void printprime(){
    Print<n + 1, 2>::print(); // n + 1 是为了让范围包括n
    }
};



int main() {
    cout << IsEven<123>::r << endl; //编译期就已经确定了r的值，运行期直接输出这个值
    cout << IsEven<124>::r << endl;
    cout << Add<97, 87>::r << endl;
    cout << Sum<10>::r << endl;
    cout << Sum<100>::r << endl;
    cout << Factorial<5>::r << endl;
    cout << Factorial<10>::r << endl;
    cout << IsPrime<9973>::r << endl;
    cout << IsPrime<87>::r << endl;
    cout << IsPrime<1537>::r << endl;
    cout << IsPrime<65>::r << endl;
    cout << SumPrime<10>::r << endl;
    PrintPrime<10>::printprime();
    PrintPrime<1>::printprime();
    return 0;
}

