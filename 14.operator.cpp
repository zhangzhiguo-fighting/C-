#include <iostream>
using namespace std;

namespace haizei { //命名空间

class istream {
public:
    istream &operator>>(int &n) { //返回值也是一个引用类型，减少了一次拷贝
        std::cin >> n;
        return *this; //返回cin类型，才能支持连续右移
    }
private:

};

class ostream {
public:
    //类内重载
    ostream &operator<<(int &n) { //返回值类型是我们可以随意设置的,想象力
        std::cout << n;
        return *this;
    }
    ostream &operator<<(const char *msg) {
        std::cout << msg;
        return *this;
    }
private:

};
istream cin;
ostream cout;

};

//重载不能改变 运算符的优先等级和参数个数
haizei::ostream &operator<<(haizei::ostream &out, double &z) {
    std::cout << z;
    return out;
}

ostream &operator+(ostream &out, const int &z) { //不加const，z就会绑定在一个变量上，变量会随着z的改变而改变，但是在这里我们传进来的是常量
    out << z;
    return out;
}

int main() {
    int n, m;
    haizei::cin >> n >> m; //系统会自动进行转换haizei::cin.operator>>(n),cin对象的operator>>方法。 cin >> n 返回一个void类型， 所以不能连续输入
    haizei::cout << n << " " << m << "\n";
    double k = 5.6;
    haizei::cout << k << "\n";
    (((((cout + 8) << " ") +  9) << " ") + 10) << "\n"; //传入的字面量，加括号是为了解决优先级冲突的问题
    return 0;
}

