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
    int n; cin >> n;
    vector<ll> a(n); cin >> a;

    map<ll, int> m;
    for(int i=0; i<n; i++){
        m[a[i]]++;
    }
    vector<pair<ll, int>> v(m.begin(), m.end());

    if(n%3){
        if(v.size()==1 && v[0].first == 0){
            cout << "Yes" << endl;
        } else {
            cout << "No" << endl;
        }
    } else {
        if(v.size()==3){
            if((v[0].first^v[1].first)==v[2].first && v[0].second==v[1].second && v[1].second==v[2].second){
                cout << "Yes" << endl;
            } else {
                cout << "No" << endl;
            }
        } else if(v.size()==2){
            if(v[0].first == 0 && v[0].second==n/3){
                cout << "Yes" << endl;
            } else {
                cout << "No" << endl;
            }
        } else if(v.size()==1){
            if(v[0].first == 0){
                cout << "Yes" << endl;
            } else {
                cout << "No" << endl;
            }
        } else {
            cout << "No" << endl;
        }
    }
    return 0;
}
