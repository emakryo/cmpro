#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

template<typename T>
ostream& operator<<(ostream &os, vector<T> &v){
    string sep = " ";
    if(v.size()) os << v[0];
    for(int i=1; i<v.size(); i++) os << sep << v[i];
    return os;
}

template<typename T>
istream& operator>>(istream &is, vector<T> &v){
    for(int i=0; i<v.size(); i++) is >> v[i];
    return is;
}

#ifdef DBG
void debug_(){ cout << endl; }
template<typename T, typename... Args>
void debug_(T&& x, Args&&... xs){
    cout << x << " "; debug_(forward<Args>(xs)...);
}
#define dbg(...) debug_(__VA_ARGS__)
#else
#define dbg(...)
#endif

int main() {
    ios_base::sync_with_stdio(false);
    cout << setprecision(20) << fixed;

    string s;
    cin >> s;

    ll damage = 0;
    int combo = 0;
    int wait = 0;
    int ball = 5;
    multimap<int, ll> damage_queue;
    map<int, int> ball_queue;
    for(int i=0; i<s.size(); i++){
        char c = s[i];
        while(damage_queue.size()&&damage_queue.begin()->first<=i){
            damage += damage_queue.begin()->second;
            combo++;
            damage_queue.erase(damage_queue.begin()->first);
        }
        while(ball_queue.size()&&ball_queue.begin()->first<=i){
            ball += ball_queue.begin()->second;
            ball_queue.erase(ball_queue.begin()->first);
        }
        if(wait>0){
            wait--;
            continue;
        }
        if(c == 'N' && ball >= 1){
            ball--;
            ball_queue[i+7] += 1;
            damage_queue.insert({i+2, 10 + combo/10});
        } else if(c == 'C' && ball >= 3){
            wait = 2;
            ball-=3;
            ball_queue[i+9] += 3;
            damage_queue.insert({i+4, 50 + combo/10*5});
        }
    }

    for(auto p: damage_queue){
        damage += p.second;
    }
    cout << damage << endl;
    return 0;
}