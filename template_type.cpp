#include <iostream>
using namespace std;

template<typename T>
void my_swap(T &&a, T &&b) {
    typename remove_reference<T>::type c; //去掉引用后的类型
    c = a;
    a = b;
    b = c;
    return ;
}

template<typename T>
void add(T &&a, T &&b) {
    a += 3;
    b += 4;
    return ;
}

void func(void (*p)(int &, int &), int &a, int &b) { //传入一个返回值为void,参数类型为两个int型引用的函数；
    p(a, b);
    return;
}

int main() {
    int a = 123, b = 345;
    my_swap(a, b); //传入一个左值，然而my_swap要接受一个引用，所以T会被推导为int &
    cout << a << " " << b << endl;
    my_swap(move(a), move(b));
    cout << a << " " << b << endl;
    func(add, a, b);
    cout << a << " " << b << endl;
    return 0;
}

