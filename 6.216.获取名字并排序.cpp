#include <iostream>
#include <set>
#include <string>
using namespace std;

typedef pair<string, int> PSI;

int main() {
    set <pair<string, int>> s;
    string name;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> name; //name 每次输入前会自动清空
        name = name.substr(name.find(".") + 1, name.size()); //要查找的字符串的首地址,如果截取的位数过大，strsub会自动截取到末尾
        s.insert(PSI(name, i));
    }
    for (auto iter = s.begin(); iter != s.end(); iter++) {
        cout << iter->first << endl;
    }
    return 0;
}

