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

class Point {
public :
    Point() {
        cout << "constructor : " << this << endl;
        Point::total_cnt += 1; //显式调用，total_cnt += 1 隐式调用
    }
    Point(const Point &a) : Point() { //拷贝构造函数
        cout << "copy constructor : " << this << endl;
        this->x = a.x;
        this->y = a.y;
    }
    Point(double z) : Point() {
        cout << "convert constructor : " << this << endl;
        this->x = 99, this->y = 99;
    }
    Point(int x, int y) : Point() {
        cout << "param constructor : " << this << endl;
        this->x = x;
        this->y = y;
    }

    void operator=(const Point &a) {
        cout << "operator= : " << this << endl;
        this->x = a.x, this->y = a.y;
        return ;
    }
    void set(int x, int y) {
        this->x = x;
        this->y = y;
    }

    //记录每个对象调用该对象方法的次数
    void seek() const {
        seek_cnt += 1;
        cout << x << " " << y << endl;
    }

    void s() const{
        cout << seek_cnt << endl;
    }
    
    //记录对象的个数
    static int T() { return Point::total_cnt; }

    ~Point() {
        cout << "destructor : " << this << endl;
        Point::total_cnt -= 1;
    }

private:
    int x, y;
    mutable int seek_cnt = 0; //使用mutable修饰的变量的值，可以在const方法里面被修改
    static int total_cnt; //static 修饰的为类属性或者类方法
};
int Point::total_cnt = 0; //类属性的初始要放在类外面

void test() {
    Point a;
    cout << Point::T() << endl;
    return ;
}


int main() {
    Point a;
    cout << a.T() << endl; //成员函数可以调用类方法和成员方法
    test();
    Point b;
    cout << b.T() << endl;
    Point c(3, 4);
    cout << c.T() << endl;
    Point d(3.4);
    cout << d.T() << endl;
    c = 5.6; //难点，理解
    cout << c.T() << endl;
    cout << &a << endl;
    cout << &b << endl;
    cout << &c << endl;
    cout << &d << endl;
    d.seek();
    c.seek();
    const Point e(6, 7);
    e.seek();
    e.seek();
    e.seek();
    e.seek();
    e.s();
    return 0;
}
