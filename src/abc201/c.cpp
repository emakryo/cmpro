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

    int ans = 0;
    for(int i=0; i<10; i++){
        for(int j=0; j<10; j++){
            for(int k=0; k<10; k++){
                for(int l=0; l<10; l++){
                    bool ok = true;
                    for(int p=0; p<10; p++){
                        if(s[p]=='o'){
                            if(i!=p&&j!=p&&k!=p&&l!=p){
                                ok = false;
                            }
                        }
                        if(s[p]=='x'){
                            if(i==p||j==p||k==p||l==p){
                                ok = false;
                            }
                        }
                    }

                    if(ok) ans++;
                }
            }
        }
    }

    cout <<ans << endl;
    return 0;
}