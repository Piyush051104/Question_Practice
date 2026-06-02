#include <bits/stdc++.h>
using namespace std;
class Test{
    public:
    string name;
    int age;

    void setdata(string name,int age){
        this -> name = name;
        this -> age = age;
    }

};

class child : public Test{

    public:
    Test* ch;



    void set(string name,int age){
        setdata(name,age);
        
    }
};
int main(){
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    
    return 0;
}