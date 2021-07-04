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

void solve(){
    int n;
    cin >> n;
    vector<int> p(n);
    cin >> p;

    map<int, int> me, mo;
    for(int i=0; i<n; i++) p[i]--;

    for(int i=0; i<n-1; i++){
        if(p[i]>p[i+1]){
            if(i%2==0) me[p[i]] = i;
            else mo[p[i]] = i;
        }
    }

    int b = 0;
    vector<int> ans;
    while(me.size()||mo.size()){
        dbg("a", b, me.size(), mo.size());
        if(b%2==0){
            if(me.size()==0){
                dbg("b", 0);
                swap(p[0], p[1]);
                ans.push_back(1);
                me.erase(p[0]);
                mo.erase(p[0]);
                if(p[0]>p[1]){
                    me[p[0]] = 0;
                }
                me.erase(p[1]);
                mo.erase(p[1]);
                if(p[1]>p[2]){
                    mo[p[1]] = 1;
                }
            } else {
                auto q = me.rbegin();
                int i = q->second; // even
                dbg("c", i);
                ans.push_back(i+1);
                swap(p[i], p[i+1]);
                me.erase(p[i]);
                mo.erase(p[i]);
                if(i>0){
                    me.erase(p[i-1]);
                    mo.erase(p[i-1]);
                    if(p[i-1]>p[i]){
                        mo[p[i-1]] = i-1;
                    }
                }

                me.erase(p[i+1]);
                mo.erase(p[i+1]);
                if(i+2<n&&p[i+1]>p[i+2]){
                    mo[p[i+1]] = i+1;
                }
            }
        } else {
            if(mo.size()==0){
                dbg("d", 1);
                swap(p[1], p[2]);
                ans.push_back(2);
                me.erase(p[1]);
                mo.erase(p[1]);
                if(p[1]>p[2]){
                    mo[p[1]] = 1;
                }
                me.erase(p[0]);
                mo.erase(p[0]);
                if(p[0]>p[1]){
                    me[p[0]] = 0;
                }
                me.erase(p[2]);
                mo.erase(p[2]);
                if(n>=3&&p[2]>p[3]){
                    me[p[2]] = 2;
                }
            } else {
                auto q = mo.rbegin();

                int i = q->second; // odd
                dbg("e", i);
                ans.push_back(i+1);
                swap(p[i], p[i+1]);
                me.erase(p[i]);
                mo.erase(p[i]);
                if(i>0){
                    me.erase(p[i-1]);
                    mo.erase(p[i-1]);
                    if(p[i-1]>p[i]){
                        me[p[i-1]] = i-1;
                    }
                }

                me.erase(p[i+1]);
                mo.erase(p[i+1]);
                if(i+2<n&&p[i+1]>p[i+2]){
                    me[p[i+1]] = i+1;
                }
            }
        }
        b++;
        dbg("f", p);
    }

    cout << ans.size() << endl;
    cout << ans << endl;
}


int main() {
    ios_base::sync_with_stdio(false);
    cout << setprecision(20) << fixed;

    int t;
    cin >> t;

    for(int i=0; i<t; i++){
        solve();
    }
    return 0;
}