#include <iostream>
#include <cstring>
using namespace std;



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
    //copy_constructor
    String(const String &str) : strLength(str.strLength) {
        if (nullptr == str.p_str){ return ; }
        //this->strLength = str.strLength;
        this->p_str = new char[512];
        strcpy(this->p_str, str.p_str);
    }
    
    char *get_p_str() {
        return this->p_str;
    }
    int get_strLength() {
        return this->strLength;
    }
    
    //operator compare
    bool operator==( String &str) {
        if (strcmp(this->p_str, str.p_str) == 0) return true;
        return false;
    }
    bool operator>( String &str) {
        if (strcmp(this->p_str, str.p_str) > 0) return true;
        return false;
    }
    bool operator<( String &str) {
        if (strcmp(this->p_str, str.p_str) < 0) return true;
        return false;
    }
    bool operator!=( String &str) {
        if (strcmp(this->p_str, str.p_str) != 0) return true;
        return false;
    }
    
    //operator+=
     String &operator+=( String &str) { //返回调用的对象
        this->strLength += str.strLength;
        char *p_old = this->p_str;
        this->p_str = new char[this->strLength];
        strcpy(this->p_str, p_old);
        strcat(this->p_str, str.p_str);
        delete[] p_old;
        return *this;
        
        /* String ret;
        ret.strLength = this->strLength + str.strLength;
        ret.p_str = new char[ret.strLength + 1];
        strcpy(ret.p_str, this->p_str);
        strcat(ret.p_str, str.p_str);
        return ret;*/ //返回值不符合要求
    }

    //operator=
     String &operator=(String &str) {
        this->strLength = str.strLength;
        strcpy(this->p_str, str.p_str);
        return *this;
     }

    friend istream &operator>>(istream & , const  String & );
    friend ostream &operator<<(ostream & , const  String & );
    friend String operator+(const  String & , const  String & );

private:
    char *p_str;
    int strLength;
};


//operator>>
istream &operator>>(istream &in, const String &str) {
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
ostream &operator<<(ostream &out, const String &str) {
    if (str.p_str != nullptr) out << str.p_str;
    return out;
}  

//operator+
 String operator+(const  String &str1, const  String &str2) {
     String ret;
    ret.strLength = str1.strLength + str2.strLength;
    ret.p_str = new char[ret.strLength + 1];
    strcpy(ret.p_str, str1.p_str);
    strcat(ret.p_str, str2.p_str);
    return ret;
}


int main() {
     String str1, str2;
    cin >> str1 >> str2;
    str1 += str2;
    cout << str1 << endl;
    str1 = str2;
    cout << str1 << endl;
    return 0;
}

