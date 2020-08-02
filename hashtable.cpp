#include <iostream>
#include <cstring>

using namespace std;


class Node {
public:


private:
    bool flag;
    char *str;
};

class HashFunc {
public:
   virtual int operator() (const char *str) const = 0; 

private:

};

class HashTable {
public:
    HashTable(HashFunc);
    bool insert(const char *str);
    bool find(const char *str);
private:
    int __size;
    Node *data;
    HashFunc *func;


};



int main() {
    
    return 0;
}

