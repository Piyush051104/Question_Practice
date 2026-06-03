#include<bits/stdc++.h>
using namespace std;
class Talkable{
    public:
    virtual void Talk() = 0;
};

class NormalTalk:public Talkable{
    public:
    void Talk() override{
        cout << "Its a Normal Talk" << endl;
    }
};

class SweetTalk:public Talkable{
    public:
    void Talk() override{
        cout << "Its a Sweettalk" << endl;
    }
};

class Flyable{
    public:
    virtual void Fly() = 0;
};

class NormalFly:public Flyable{
    public:
    void Fly(){
        cout << "Its a normal fly" << endl;
    }
};

class SpeedFly:public Flyable{
    public:
    void Fly(){
        cout << "Its a Speed fly" << endl;
    }
};


class Robot{
    private:
    Talkable* ta;
    Flyable* fe;
    public:
    Robot(Talkable* ta,Flyable* fe){
        this->ta = ta;
        this->fe = fe;
    }
    
    void Talk(){
        ta->Talk();
    }
    void fly(){
        fe->Fly();
    }
};

int main(){
    Talkable* te = new NormalTalk();
    Flyable* fe = new SpeedFly();
    Robot* ro = new Robot(te,fe);

    ro->Talk();
    ro->fly();
}



