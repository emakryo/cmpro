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
    int a, b, k;
    cin >> a >> b >> k;

    if(a==0){
        if(k==0){
            cout << "Yes" << endl;
            cout << string(b, '1') << endl;
            cout << string(b, '1') << endl;
        } else {
            cout << "No" << endl;
        }
        return 0;
    }

    if(b==1){
        if(k==0){
            cout << "Yes" << endl;
            cout << "1" + string(a, '0') << endl;
            cout << "1" + string(a, '0') << endl;
        } else {
            cout << "No" << endl;
        }
        return 0;
    }

    if(k>a+b-2){
        cout << "No" << endl;
        return 0;
    }

    cout << "Yes" << endl;
    cout << string(b, '1') + string(a, '0') << endl;
    int x = a+b-1-k;
    if(b-x-1>=0) cout << string(x, '1') + "0" + string(b-x-1, '1') + string(a-1, '0') + "1" << endl;
    else cout << string(b-1, '1') + string(k, '0') + "1" + string(a-k, '0') << endl;
    return 0;
}