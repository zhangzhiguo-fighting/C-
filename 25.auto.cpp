#include <iostream>
#include <map>
using namespace std;


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
    return 0;
}

