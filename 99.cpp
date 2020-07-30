#include <iostream>
#include <cstring>
using namespace std;

namespace haizei {

class String {
public:
    
    //constructor
    String() : p_str(nullptr), strLength(0){
        p_str = new char[512];
        cout << "constructor" << endl;
    }
    String(const char *str) : String() {
        if(nullptr == str) { return ; }
        this->strLength = strlen(str);
        this->p_str = new char[strLength + 1];
        strcpy(this->p_str, str);
        cout << "prameter_constructor" << endl;
    }
    String(const String &str) : String() {
        if (nullptr == str.p_str){ return ; }
        this->strLength = str.strLength;
        this->p_str = new char[strLength + 1];
        strcpy(this->p_str, str.p_str);
        cout << "copy_constructor" << endl;
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
    bool operator<=(const haizei::String &str) {
        return (strcmp(this->p_str, str.p_str) < 0 || strcmp(this->p_str, str.p_str) == 0) ? true : false;
    }
    bool operator>=(const haizei::String &str) {
        return (strcmp(this->p_str, str.p_str) > 0 || strcmp(this->p_str, str.p_str) == 0) ? true : false;
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
    haizei::String operator+(const haizei::String &str) {
        haizei::String ret;
        ret.strLength = this->strLength + str.strLength;
        ret.p_str = new char[ret.strLength + 1];
        strcpy(ret.p_str, this->p_str);
        strcat(ret.p_str, str.p_str);
        return ret;
    }
    
    //operator[]
    char &operator[](int index) {
        //if (index < 0 || index >= this->strLength) throw Outofbond;
        return this->p_str[index];
    }

    //operator=
    haizei::String &operator=(const haizei::String &str) {
        this->p_str = str.p_str;
        this->strLength = str.strLength;
        cout << "operator=" << endl;
        return *this;
    }
    

    ~String() {
        //delete[] this->p_str;
        //cout << "destructor" << endl;
    }

    friend istream &operator>>(istream &, const haizei::String &);
    friend ostream &operator<<(ostream &, const haizei::String &);

private:
    char *p_str;
    int strLength;
};


//operator>>
istream &operator>>(istream &in, const haizei::String &str) {
    /*char tmp[100];
    if (in >> tmp) {
        delete[] str.p_str; //清空以前的数据
        str.strLength = strlen(tmp);
        str.p_str = new char[str.strLength + 1];
        strcpy(str.p_str, tmp);
    }*/
    in >> str.p_str;
    return in;
}

//operator<<
ostream &operator<<(ostream &out, const haizei::String &str) {
    if (str.p_str != nullptr) out << str.p_str;
    return out;
}  

};


int main() {
    haizei::String a, b, c;
    cin >> a;
    b = "fangsong";
    c = a + b;
    cout << c << endl;
    cout << a + b << endl;
    cout << b << endl;
    cout << b[0] << endl;
    b[0] = 'a';
    cout << b[0] << endl;
    b += c;
    cout << b << endl;
    if(a == b) {
        cout << "a == b" << endl;
    } else if(a > b) {
        cout << "a > b" << endl;
    } else if(a < b) {
        cout << " a < b" << endl;
    } else if(a != b) {
        cout << "a != b" << endl;
    }
    cout << "---------------" << endl;
    haizei::String d;
    d = "wwwwwwwww";
    haizei::String e = d;
    cout << d << endl;
    cout << e << endl;
    e = "xiugai";
    cout << " ----------------" << endl;
    cout << d << endl;
    cout << e << endl;

    return 0;
}
