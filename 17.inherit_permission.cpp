#include <iostream>
using namespace std;

class Animal {
public:
    Animal(string name, int age) : __name(name), age(age) {}
    void say() {
        cout << "my name is : " << __name << ", my age is : " << age << endl;
        //子类存储了父类中全部的数据，因为功能的完整性取决于数据的完整性。
        return ;
    }

protected:
    string __name;

private:
    int age; //成员属性的声明, 没有对象就没有age，有一个对象就有一个age，所以它是一个声明，不占内存空间（存不存在与对象有关系）
};

class Cat : public Animal {
public:
    Cat() = delete;
    Cat(string name, int age) : Animal(name, age) {}
};

class Bat : protected Animal { //protected不影响Bat类对Animal类的访问权限，Bat类中的say变为protected权限
public:
    Bat() = delete;
    Bat(string name, int age) : Animal(name, age) {}
    void say() {
        this->Animal::say(); //先调用当前对象父类Animal中的say方法，this不写系统也会补全
        cout << "class Bat:" << __name << endl; //子类访问父类protected权限的成员属性
        //cout << "class Bat:" << age << endl; //错误示范，子类访问父类的private权限的成员属性
        return ;
    }
};

int main() {
    Cat a("tom", 20);
    a.say();
    Bat b("fly", 1573);
    b.say();
    return 0;
}

