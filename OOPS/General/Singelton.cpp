#include <bits/stdc++.h>
using namespace std;
class user{
private:
    static user* us;
    static mutex mtx;

    user(){
        cout << "user is created" << endl;
    }
public:
    static user* createuser(){
        if(us == nullptr){
            lock_guard<mutex> lock(mtx);
            if(us == nullptr){
                us = new user();
            }   
        }
        return us;
    }
};

user* user::us = nullptr;
mutex user::mtx;
int main(){
    ios_base::sync_with_stdio(false); cin.tie(nullptr);

    user* us1  = user::createuser();
    user* us2 = user::createuser();

    cout << (us1 == us2) << endl;
    
}