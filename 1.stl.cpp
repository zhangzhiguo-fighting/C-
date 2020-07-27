#include <iostream>
#include <queue>
#include <string>
using namespace std;

int main() {
    int op, val;
    queue<int> q;
    while (cin >> op >> val) {
        switch (op) {
        case 1: q.push(val); break;
        case 2: q.pop(); break;
        case 3: cout << q.front() << endl; break;
        }
        //cout << "queue size : " << q.size() << ", empty : " << (q.empty() ? "true" : "false") << endl;
        printf("queue size : %ld, empty : %s\n", q.size(), q.empty() ? "true" : "false");
    }
    return 0;
}

