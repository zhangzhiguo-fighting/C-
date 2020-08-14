#include <iostream>
#include <map>
#include <string>
using namespace std;


string randstring(int n) {
    string ret = "";
    for (int i = 0; i < n; i++) {
        char ch = rand() % 26 + 'A';
        ret += ch;
    }
    return ret;
}

int my_seed = 1;
void my_srand(int seed) { // 如果seed值不发生变化，每次将是伪随机（一个串起来的链，每次起点一致，下一次是可以确定的），输出结果一样
    my_seed = seed;
}

int my_rand() {
    my_seed = my_seed * 3 % 101;
    return my_seed;
}

int main() {
    auto a = 123; //编译阶段就能确定
    cout << sizeof(a) << endl;
    map<int, int> arr;
    arr[712564] = 12341;
    arr[32123] = 454;
    arr[888] = 10000;
    //auto
    for (map<int, int>::iterator iter = arr.begin(); iter != arr.end(); iter++) {
        cout << iter->first << " " << iter->second << endl;
    }
    for (auto x : arr)  { //C++11引进
        cout << x.first << " " << x.second << endl;
    }
    

    long long b[100] = {0};
    auto c = b; //auto 被推导为指针类型，因为b是一个地址
    cout << sizeof(c) << endl;

    // 随机函数原理（伪随机）
    my_srand(time(0)); //随机种子，给予一个随时都在发生变化的整数
    srand(time(0));
    map<string, int> ind;
    for (int i = 0; i < 10; i++) {
        ind[randstring(rand() % 10 + 3)] = rand();
    }
    auto iter = ind.begin();
    for ( ; iter != ind.end(); iter++) {
        cout << iter->first << " " << iter->second << endl;
    }
    for (auto x : ind) {
        cout << x.first << " " << x.second << endl;
    }
    return 0;
}

