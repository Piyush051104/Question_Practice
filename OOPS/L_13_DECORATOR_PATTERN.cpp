#include <bits/stdc++.h>
using namespace std;

class firstclass{
    public:

};

class childclass : public firstclass{
    public:
    int x;

    childclass(int x){
        this->x = x;
        cout << x << endl;
    }
};
int main(){
    childclass* ch = new childclass(5);
}