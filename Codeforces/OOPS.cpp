#include <bits/stdc++.h>
using namespace std;
class Vehicle{
public:
    string name;
    string model;
    int noOfTyres;
public:
    void start_engine(){
        cout << "Engine is starting " << name << " " << model << endl;
    }
    void stop_engine(){
        cout << "Engine is stoping " << name << " " << model << endl;
    }
};

class Car:public Vehicle{
public:
    int noOfdoors;
    string transmissiontype;

    void startAc(){
        cout << "Ac has started of car" <<" " << name << endl;
    }

};

int main(){
    
}