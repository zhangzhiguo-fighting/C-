#include <iostream>
using namespace std;

//当有内重载时，优先调用内重载
class Point {
public:
    Point() : __x(0), __y(0){}
    Point(int x, int y) : __x(x), __y(y) {}
    int x() const { return __x; } //加上const为了方便，后面的const对象调用此方法,其他对象也可以调用const方法
    int y() const { return __y; }
    
    Point operator+(const Point &a) { //返回一个新的点
        return Point(x() + a.x(), y() + a.y());
    }
    
    Point &operator+=(const Point &a) {
        __x += a.x();
        __y += a.y();
        return *this;
    }

    Point &operator++() { //前++，返回的还是对象c
        __x += 1;
        __y += 1;
        return *this;
    }
    Point operator++(int) { //int仅用来区分前++和后++；不能返回引用，temp在函数结束时会被析构
        Point temp(*this); //返回+1前的值，调用系统默认的复制构造函数
        __x += 1;
        __y += 1;
        return temp;
    }

private:
    int __x, __y;
};


ostream &operator<<(ostream &out, const Point &a) {
   out << "Point (" << a.x() << ", " << a.y() << ")"; //只有const对象能调用const类型的方法
   return out;
}


int main() {
    Point a, b(3, 4), c(1, 1);
    cout << a << endl;
    cout << b << endl;
    cout << c << endl;
    //cout << a << " " << b << endl;
    cout << a + b << endl;
    //c += b;
    cout << "pre incr : " << ++(c += b) << endl;
    cout << c << endl;
    //c++;
    cout << "after incr : " << c++ << endl;
    cout << c << endl;
    int n = 6, m = 7;
    (n += m)++;
    cout << n << endl;
    return 0;
}

