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

template<typename T>
ostream& operator<<(ostream &os, multiset<T> &v){
    string sep = " ";
    auto it = v.begin();
    if(it!=v.end()) os << *it;
    else return os;
    for(it++; it!=v.end(); it++) os << sep << *it;
    return os;
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
    int h, w;
    cin >> h >> w;

    vector<int> a(h), b(h);
    for(int i=0; i<h; i++) cin >> a[i] >> b[i];

    map<int, int> s, r;
    r[0] = w;
    for(int i=1; i<=w; i++){
        s[i] = i;
    }

    for(int i=0; i<h; i++){
        int x = 0;
        for(auto it=s.lower_bound(a[i]); it!=s.end()&&it->first<=b[i]; it=s.erase(it)){
            if(--r[it->first-it->second] == 0) r.erase(it->first-it->second);
            x = max(x, it->second);
        }
        if(s.count(b[i]+1)){
            int k = s[b[i]+1];
            x = max(x, k);
            if(--r[b[i]+1-k] == 0) r.erase(b[i]+1-k);
        }

        if(x>0&&b[i]<w){
            s[b[i]+1] = x;
            r[b[i]+1-x]++;
        }
        cout << (r.size()>0 ? r.begin()->first+i+1 : -1) << "\n";
    }
    return 0;
}
