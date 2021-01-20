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

    vector<int> id;
    while(cin>>buf){
        int n=0;
        for(int i=0; i<10; i++){
            n*=2;
            if(buf[i]=='B' || buf[i]=='R') n++;
        }
        // dbg(buf, n);
        id.push_back(n);
    }
    sort(id.begin(), id.end());
    dbg(id.size());

    for(int i=0; i+1<id.size(); i++){
        if(id[i+1]-id[i]!=1){
            dbg(i, id[i], id[i+1]-id[i]);
            cout << id[i]+1 << endl;
            // return 0;
        }
    }

    return 0;
}