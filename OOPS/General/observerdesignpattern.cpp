#include <bits/stdc++.h>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;
class Isubscriber{
public:
    virtual void update() = 0;
    virtual ~Isubscriber(){};
};
class Ichannel{
public:
    virtual void subscribe(Isubscriber* sub) = 0;
    virtual void unsubscribe(Isubscriber* sub) = 0;
    virtual void notify() = 0;
    virtual ~Ichannel(){};
};

class channel: public Ichannel{
public:
    set<Isubscriber*>list;
    string name;
    string latestvideo;

    channel(string name){
        this->name = name;
    }


    void subscribe(Isubscriber* sub) override {
        list.insert(sub);
        cout << "New subscriber added" << endl;
    }

    void unsubscribe(Isubscriber* sub) override {
        if(list.find(sub) != list.end()) list.erase(sub);
        cout << "Someone Unsubsribed" << endl;
    }

    void notify(){
        for(auto &sub:list){
            sub->update();
        }
    }

    void uploadvideo(){
        cout << "New video uploaded" << endl;
        notify();
    }

    string getvideo(){
        return "Yours video";
    }
};

class subscriber:public Isubscriber{
public:
    channel* ch;

    subscriber(channel* ch){
        this->ch = ch;
    }
    void update() override{
        cout << "update" << ch->getvideo() << endl;
    }    
};

int main(){
    channel* ch = new channel("DSA ARMY");

    subscriber* sub1 = new subscriber(ch);
    subscriber* sub2 = new subscriber(ch);

    ch->subscribe(sub1);
    ch->subscribe(sub2);

    ch->unsubscribe(sub1);
    ch->uploadvideo();

}