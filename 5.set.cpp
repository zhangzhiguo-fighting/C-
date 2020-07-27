#include <iostream>
#include <set>
using namespace std;

int main() {
    set<int> s;
    //heap<int> //堆
    s.insert(345);
    s.insert(65);
    s.insert(9973);
    s.insert(9000);
    cout << s.size() << endl;
    s.insert(65);
    cout << s.size() << endl; //返回独立元素的个数
    cout << *(s.begin()) << endl; //返回值最小的数
    for (auto iter = s.begin(); iter != s.end(); iter++) {
        cout << *iter << endl;
    }
    s.erase(s.begin());
    cout << *(s.begin()) << endl;
    return 0;
    //在乎数据结构的外在变表现，不在乎底层实现，但要理解底层的实现，从效果看set可以模拟堆
}
