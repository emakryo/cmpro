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

    int n;
    cin >> n;
    if(n%2) return 0;

    vector<string> ans(1, "(");
    for(int i=0; i<n-1; i++){
        vector<string> next;
        for(string x: ans){
            int k = 0;
            for(int j=0; j<x.size(); j++){
                if(x[j]=='(') k++;
                else k--;
            }
            if(k<n-x.size()) next.push_back(x + '(');
            if(k>0) next.push_back(x + ')');
        }
        ans = next;
    }

    for(string x: ans){
        cout << x << "\n";
    }
    return 0;
}