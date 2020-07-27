#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <queue>
#include <stack>
#include <algorithm>
#include <string>
#include <map>
#include <set>
#include <vector>
using namespace std;

class People {
public :
    //People() {}
    People() = default; //将隐形的规则转换为可见的规则，方便调试
    //People() = delete;
    People(string name) {
        cout << "param constructor" << endl;
        this->name = name;
    }
    People(int x) {
        cout << "int param constructor" << endl;
        this->x = x;
    }
    People(const People &a) {
        cout << "copy constructor" << endl;
        this->name = a.name;
        this->x = a.x;
    }
    
    void operator=(const People &a) {
        cout << "operator =" << endl;
        this->name = a.name;
        this->x = a.x;
        return ;
    }

    ~People() {
        cout << "destructor" << endl;
    }
    string name;
    int x;
};

void incr(int &a) {
    a += 1;
    return ;
}

int add(People a, People b) {
    return a.x + b.x;
}

int main() {
    int n = 7;
    incr(n);
    cout << n << endl;
    cout << add(4, 5) << endl;
    People a("hug");
    People b = string("hug");
    People c(543);
    People d = 678;
    cout << a.name << endl;
    cout << b.name << endl;
    cout << c.x << endl;
    cout << d.x << endl;
    c = 987;
    cout << c.x << endl;
    d = string("duanchenyang");
    cout << d.name << endl;
    People e = a;
    cout << e.name << endl;
    cout << e.x << endl;
    c = a;
    cout << c.name << endl;
    cout << c.x << endl;
    return 0;
}

