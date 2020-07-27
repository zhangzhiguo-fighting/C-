#include <iostream>
using namespace std;

class People {
public:
    People(){}
    People(string name) {
        this->name = name;
    }
    People(int x) {
        this->x = x;
    }
    /*People() { 默认构造函数
        arr = new int[10];
        cout << "default constructor" << endl;
    }*/
    ~People() {
        cout << "destructor" << endl;
    }
    string name;
    int x;
    //int *arr;
};

void incr(int &a) {
    a += 1;
    return;
}

int main() {
    int w = 7;
    incr(w);
    cout << w << endl;
    People b("ggbal");
    People a = string("string"); //调用string类的构造函数进行类型转换
    People c(54);
    //a.arr[9] = 12
    cout << a.name << endl;
    c = 987; //一个参数的有参构造函数被称为转换构造函数
    cout << c.x << endl;
    People d = string("fsdaf");
    cout << d.name << endl;
    return 0;
}
