#include <iostream>
using namespace std;

int f(int x) {
    cout << "output int value : ";
    cout << x << endl;
    return 0;
}

int f(int *x) {
    cout << "output address : ";
    cout << x << endl;
    return 0;
}

int main() {

    printf("%lld\n", (long long)nullptr);
    //cout << nullptr << endl;
    cout << NULL << endl;
    int n = 123, *p = &n;
    f(n);
    f(p);
    f(nullptr); //严格意义上本质是个地址
    f((int)NULL); //本质是整型0， (void *)0，但我们当成地址去看，不严谨，容易造成编译器混淆
    return 0;
}

