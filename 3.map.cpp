#include <iostream>
#include <map>
#include <unordered_map>
using namespace std;

int main() {
    //unordered_map<double, string> arr;
    map<double, string> arr;
    arr[1.2] = "hellow"; //将对应关系（1.2, "hello"）打包，作为结点
    arr[4.3] = "world";
    arr[-4.5] = "haizei";
    arr[89.7] = "world";

    double n;
    while (cin >> n) {
        if (arr.find(n) != arr.end()) { //arr[n] != " "  一查看就会多一个结点，会影响map效率
            cout << "find : " << arr[n] << endl;
        } else {
            cout << " not found : " << n << endl;
        }
    }


    for (auto iter = arr.begin(); iter != arr.end(); iter++) {
        cout << iter->first << " " << iter->second << endl;
    }
    return 0;
}
