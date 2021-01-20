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

    vector<pair<char, int>> instructions;
    char a;
    int n;
    while(cin >> a >> n){
        instructions.push_back({a, n});
        dbg(a, n);
    }

    int x = 0, y = 0;
    int wx = 10, wy = 1;

    for(int i=0; i<instructions.size(); i++){
        a = instructions[i].first;
        n = instructions[i].second;

        if(a=='F'){
            x += n*wx;
            y += n*wy;
        }

        if(a=='N') wy+=n;
        if(a=='E') wx+=n;
        if(a=='S') wy-=n;
        if(a=='W') wx-=n;

        if(a=='L'&&n==90||a=='R'&&n==270){
            swap(wx, wy);
            wx = -wx;
        } else if(n==180){
            wx = -wx;
            wy = -wy;
        } else if(a=='L'&&n==270||a=='R'&&n==90){
            swap(wx, wy);
            wy = -wy;
        }
        dbg(x, y, wx, wy);
    }

    cout << abs(x) + abs(y) << endl;

    return 0;
}