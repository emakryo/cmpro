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

    string buf;
    vector<pair<string, int>> code;
    while(cin >> buf){
        int n; cin >> n;
        dbg(buf, n);
        code.push_back({buf, n});
    }


    for(int i=0; i<code.size(); i++){
        if(code[i].first=="acc") continue;
        if(code[i].first=="nop") code[i].first = "jmp";
        else code[i].first = "nop";

        int acc = 0;
        int ip = 0;
        vector<bool> visit(code.size());
        while(0<=ip&&ip<code.size()&&!visit[ip]){
            visit[ip] = true;
            if(code[ip].first=="acc"){
                acc+=code[ip].second;
                ip++;
            } else if(code[ip].first=="nop"){
                ip++;
            } else {
                ip+=code[ip].second;
            }
        }

        if(ip == code.size()){
            cout << acc << endl;
            return 0;
        }

        if(code[i].first=="nop") code[i].first = "jmp";
        else code[i].first = "nop";
    }

    return 0;
}