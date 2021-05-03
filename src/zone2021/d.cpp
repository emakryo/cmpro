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

    string t1, t2;
    bool f = false;
    for(char x: s){
        if(x=='R'){
            f = !f;
        } else {
            if(f){
                if(t1.size()>0&&t1.back()==x) t1.pop_back();
                else t1 += x;
            } else {
                if(t2.size()>0&&t2.back()==x) t2.pop_back();
                else t2 += x;
            }
        }
    }

    int k = 0;
    while(k<min(t1.size(), t2.size())&&t1[k]==t2[k]) k++;
    t1 = t1.substr(k);
    t2 = t2.substr(k);
    if(f){
        reverse(t2.begin(), t2.end());
        cout << t2 << t1 << endl;
    } else {
        reverse(t1.begin(), t1.end());
        cout << t1 << t2 << endl;
    }

    return 0;
}