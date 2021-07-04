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

    ll a, b, c;
    cin >> a >> b >> c;
    if(0<=a&&0<=b){
        if(a==b) cout << '=' << endl;
        else cout << (a<b?'<':'>') << endl;
    } else if(0<=a){
        if(c%2){
            cout << '>' << endl;
        } else {
            if(a==abs(b)) cout << '=' << endl;
            else cout << (a<abs(b)?'<':'>') << endl;
        }
    } else if(0<=b){
        if(c%2){
            cout << '<' << endl;
        } else {
            if(abs(a)==abs(b)) cout << '=' << endl;
            else cout << (abs(a)<abs(b)?'<':'>') << endl;
        }
    } else {
        if(c%2){
            if(abs(a)==abs(b)) cout << '=' << endl;
            else cout << (abs(a)<abs(b)?'>':'<') << endl;
        } else {
            if(abs(a)==abs(b)) cout << '=' << endl;
            else cout << (abs(a)<abs(b)?'<':'>') << endl;
        }
    }
    return 0;
}