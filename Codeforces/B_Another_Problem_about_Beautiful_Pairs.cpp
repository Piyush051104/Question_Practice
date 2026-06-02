#include <bits/stdc++.h>
using namespace std;

class Student {
public:
    static int count;
};

int Student::count = 0;

int main() {
    Student a, b;

    a.count = 5;

    cout << b.count << endl;
}