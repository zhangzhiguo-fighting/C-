#include <iostream>
#include <cstring>
using namespace std;

namespace haizei {

class string {
public:
    string() {
        cout << "string : default constructor, " << this << endl;
        this->__buff_size = 10;
        this->buff = new char [this->__buff_size];
        this->buff = nullptr;
        this->__length = 0;
    }
    string (const char *str) {
        cout << "string : const char constructor, " << this << endl;
        this->__buff_size = strlen(str) + 1;
        this->buff = new char[this->__buff_size];
        strcpy(this->buff, str);
        this->__length = this->__buff_size - 1;
    }

    string (const string &s) { //O(n)
        cout << "copy constructor, " << this << endl;
        this->__buff_size = s.__buff_size;
        this->__length = s.__length;
        this->buff = new char[this->__buff_size];
        strcpy(this->buff, s.buff);
    }
    
    string (string &&s) { //O(1)，用于匿名变量直接的拷贝，把要释放的临时空间直接做成需要开辟的空间
        cout<< "move constructor, " << this << endl;
        this->__buff_size = s.__buff_size;
        this->__length = s.__length;
        this->buff = s.buff;
        s.buff = nullptr; // 若不把先前的值指针置为空，原来的临时对象调用析构函数的时候，仍然会释放掉这边区域（即匿名对象的存储空间被释放）
    }

    char &at(int ind) {
        if (ind < 0 || ind >= __length) {
            cout << "String Error : out of range" << endl;
            return __end;
        }
        return this->operator[](ind);
    }
    char &operator[](int ind) {
        return buff[ind];
    }
    const char *c_str() const {
        return buff;
    }

    string operator+(const string &s) {
        cout << "string : operator+, " << this << endl;
        int size = this->__length + s.__length + 1;
        char *temp = new char[size];
        strcpy(temp, this->buff);
        strcat(temp, s.buff);
        /*for (int i = 0; i < size; i++) {
            cout << temp[i];
        }
        cout << endl;*/
        return temp; //会去调用转换函数，将 char* 类型转换成string类
    }
    int size() { return this->__length; }
    ~string() {
        cout << "string : destructor, " << this << endl;
        if(this->buff) delete this->buff;
    }

private:
    int __length, __buff_size;
    char *buff;
    char __end;
};

}

ostream &operator<<(ostream &out, const haizei::string &s) {
    out << s.c_str();
    return out;
}


int main() {
    haizei::string s1 = "hello world", s2 = ", haizei", s3 = ", haerbin.";
    cout << "========= s4 begin ========" << endl;
    haizei::string s4 = s1 + s2 + s3;
    cout << "========= s4 end ========" << endl;
    cout << s1 << endl;
    haizei::string s5 = s4;
    cout << s4 << endl;
    cout << s5 << endl;
    s4[3] = '=';
    cout << s4 << endl;
    cout << s5 << endl;
    s1[3] = '6';
    cout << s1 << endl;
    cout << s1 + s2 + s3 << endl;
    for (int i = 0; i < s1.size(); i++) {
        cout << s1[i] << endl;
    }
    return 0;
}

