#include <iostream>
using namespace std;

int main() {
    string s1 = "hello", s2 = "world";
    s1 += " ";
    s1 += s2;
    cout << s1 << endl;
    for (int i = 0; i < s1.size(); i++) {
        cout << s1[i] << endl; //[]是一个运算符
    }
    return 0;
}

