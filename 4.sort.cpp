#include <iostream>
#include <algorithm>
using namespace std;

bool cmp(int a, int b) {
    return a > b;
}

struct CMP_FUNC {
    bool operator()(int a, int b) {
        return a > b;
    }
};

int main() {
    int arr[1000], n;
    cin >> n;
    for (int i = 0; i < n; i++) cin >> arr[i];
    nth_element(arr, arr + 1, arr + n); //只能保证arr[1]放置的元素是正确的
    cout << arr[1] << endl;
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << endl;
    sort(arr, arr + n, cmp);
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << endl;
    return 0;
}
