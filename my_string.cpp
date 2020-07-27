#include <iostream>
#include <cstring>
using namespace std;

const int MAX = 500;

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
    }
    String(const String &str) {
        if (nullptr == str.p_str){ return ; }
        this->strLength = str.strLength;
        //memcpy(this->p_str, str.p_str, sizeof(char) * 500);
        strcpy(this->p_str, str.p_str);
    }
    
    char *get_p_str() {
        return this->p_str;
    }
    int get_strLength() {
        return this->strLength;
    }

    //operator compare
    bool operator==(haizei::String &str) {
        if (strcmp(this->p_str, str.p_str) == 0) return true;
        return false;
    }
    bool operator>(haizei::String &str) {
        if (strcmp(this->p_str, str.p_str) > 0) return true;
        return false;
    }
    bool operator<(haizei::String &str) {
        if (strcmp(this->p_str, str.p_str) < 0) return true;
        return false;
    }
    bool operator!=(haizei::String &str) {
        if (strcmp(this->p_str, str.p_str) != 0) return true;
        return false;
    }
    
    //operator+=
    haizei::String &operator+=(haizei::String &str) { //返回调用的对象
        this->strLength += str.strLength;
        char *p_old = this->p_str;
        this->p_str = new char[this->strLength];
        strcpy(this->p_str, p_old);
        strcat(this->p_str, str.p_str);
        delete[] p_old;
        return *this;
        
        /*haizei::String ret;
        ret.strLength = this->strLength + str.strLength;
        ret.p_str = new char[ret.strLength + 1];
        strcpy(ret.p_str, this->p_str);
        strcat(ret.p_str, str.p_str);
        return ret;*/ //返回值不符合要求
    }    
    //friend istream &operator>>(istream &in, haizei::String &str);
    //friend ostream &operator<<(ostream &out, haizei::String &str);

//private:
    char *p_str;
    int strLength;
};

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

//operator+
haizei::String operator+(const haizei::String &str1, const haizei::String &str2) {
    haizei::String ret;
    ret.strLength = str1.strLength + str2.strLength;
    ret.p_str = new char[ret.strLength + 1];
    strcpy(ret.p_str, str1.p_str);
    strcat(ret.p_str, str2.p_str);
    return ret;
}


int main() {
    haizei::String str1, str2;
    cin >> str1 >> str2;
    str1 += str2;
    cout << str1 << endl;
    str1 = str2;
    cout << str1 << endl;
    return 0;
}

