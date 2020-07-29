#include <iostream>
#include <cstring>
using namespace std;

namespace haizei {

class String {
public:
    
    //constructor
    String() : p_str(nullptr), strLength(0){}
    String(const char *str) {
        if(nullptr == str) { return ; }
        this->strLength = strlen(str);
        this->p_str = new char[strLength + 1];
        strcpy(this->p_str, str);
        cout << "constructor" << endl;
    }
    String(const String &str) {
        if (nullptr == str.p_str){ return ; }
        this->strLength = str.strLength;
        this->p_str = new char[strLength + 1];
        strcpy(this->p_str, str.p_str);
        cout << "copy constructor" << endl;
    }
    
    char *get_p_str() {
        return this->p_str;
    }
    int get_strLength() {
        return this->strLength;
    }

    //operator compare
    bool operator==(const haizei::String &str) {
        return (strcmp(this->p_str, str.p_str) == 0) ? true : false;
    }
    bool operator>(const haizei::String &str) {
        return (strcmp(this->p_str, str.p_str) > 0) ? true : false;
    }
    bool operator<(const haizei::String &str) {
        return (strcmp(this->p_str, str.p_str) < 0) ? true : false;
    }
    bool operator!=(const haizei::String &str) {
        return (strcmp(this->p_str, str.p_str) != 0) ? true : false;
    }
    
    //operator+=
    haizei::String &operator+=(const haizei::String &str) { //返回调用的对象
        this->strLength += str.strLength;
        char *p_old = this->p_str;
        this->p_str = new char[this->strLength + 1];
        strcpy(this->p_str, p_old);
        strcat(this->p_str, str.p_str);
        delete[] p_old;
        return *this;
    }

    //operator+
    haizei::String &operator+(haizei::String &str) {
        this->strLength += str.strLength;
        char *p_old = this->p_str;
        this->p_str = new char[this->strLength + 1];
        strcpy(this->p_str, p_old);
        strcat(this->p_str, str.p_str);
        delete[] p_old;
        return *this;
    }
    
    //operator[]
    char &operator[](int index) {
        //if (index < 0 || index >= this->strLength) throw Outofbond;
        return *(this->p_str + index);
    }

    friend istream &operator>>(istream &in, haizei::String &str);
    friend ostream &operator<<(ostream &out, haizei::String &str);

private:
    char *p_str;
    int strLength;
};


//operator>>
istream &operator>>(istream &in, haizei::String &str) {
    char tmp[100];
    if (in >> tmp) {
        delete[] str.p_str; //清空以前的数据
        str.strLength = strlen(tmp);
        str.p_str = new char[str.strLength + 1];
        strcpy(str.p_str, tmp);
    }
    return in;
}

//operator<<
ostream &operator<<(ostream &out, haizei::String &str) {
    if (str.p_str != nullptr) out << str.p_str;
    return out;
}  

};


int main() {
    haizei::String s1, s2, s3;
    cin >> s1 >> s2 >> s3;
    cout << "s1 == s2 : " << (s1 == s2) << endl;
    cout << "s1 != s2 : " << (s1 != s2) << endl;
    cout << "s1 > s2 : " << (s1 > s2) << endl;
    cout << "s1 < s2 : " << (s1 < s2) << endl;
    cout << s1[3] << endl;
    s1[3] = '4';
    cout << s1 << endl;
    s1 += s3;
    cout << s1 << endl;
    haizei::String s4 = s1 + s2 + s3;
    cout << s4 << endl;
    s4 = "haizeikeji";
    cout << s4 << endl;
    //s4(s1); 
    return 0;
}
