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

    string s1, s2, s3;
    cin >> s1 >> s2 >> s3;

    set<char> cs;
    for(char c: s1) cs.insert(c);
    for(char c: s2) cs.insert(c);
    for(char c: s3) cs.insert(c);
    if(cs.size()>10){
        cout << "UNSOLVABLE" << endl;
        return 0;
    }

    map<char, int> m;
    int n = 0;
    for(char c: cs){
        m[c] = n++;
    }

    vector<int> p(10);
    for(int i=0; i<10; i++) p[i] = i;

    do {
        ll n1=0, n2=0, n3=0;
        if(p[m[s1[0]]]==0 || p[m[s2[0]]]==0 || p[m[s3[0]]]==0) continue;
        for(int i=0; i<s1.size(); i++){
            n1 = 10*n1 + p[m[s1[i]]];
        }
        for(int i=0; i<s2.size(); i++){
            n2 = 10*n2 + p[m[s2[i]]];
        }
        for(int i=0; i<s3.size(); i++){
            n3 = 10*n3 + p[m[s3[i]]];
        }

        if(n1+n2==n3){
            cout << n1 << endl;
            cout << n2 << endl;
            cout << n3 << endl;
            return 0;
        }
    } while(next_permutation(p.begin(), p.end()));

    cout << "UNSOLVABLE" << endl;

    return 0;
}