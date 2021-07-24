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

bool check(ll state, int r, int c){
    if(r==1||c==1) return true;
    bool ok = true;
    for(int k=1; k<=min(r,c)/2; k++){
        for(int x=0; x<r-k; x++){
            for(int y=0; y<c-k; y++){
                bool sq = true;
                for(int i=0; i<k; i++){
                    if((state>>(c*(x+k-1-i)+(y+i))&1)==0) sq = false;
                    if((state>>(c*(x+k+i)+(y+i))&1)==1) sq = false;
                    if((state>>(c*(x+i)+(y+k+i))&1)==1) sq = false;
                    if((state>>(c*(x+2*k-1-i)+(y+i+k))&1)==0) sq = false;
                }

                if(sq) ok = false;
            }
        }
    }

    return ok;
}

void print(ll state, int r, int c){
    for(int x=0; x<r; x++){
        for(int y=0; y<c; y++){
            cout << ((state>>(x*c+y)&1)?'/':'\\');
        }
        cout << '\n';
    }
}

void solve(){
    int r, c;
    cin >> r >> c;
    vector<int> s(r), d(c);
    cin >> s >> d;

    vector<ll> states;
    states.push_back(0);

    for(int i=0; i<r; i++){
        vector<ll> nexts;

        for(ll state: states){
            for(ll bs=0; bs<(1<<c); bs++){
                int k = 0;
                for(int j=0; j<c; j++) k+=bs>>j&1;
                if(k!=s[i]) continue;
                ll next = state + (bs<<(c*i));

                bool ok = true;
                for(int j=0; j<c; j++){
                    int m = 0;
                    for(int l=0; l<i+1; l++){
                        m += next>>(l*c+j)&1;
                    }
                    if(m>d[j]) ok = false;
                }
                if(!ok) continue;
                dbg(i, bs, next);

                if(check(next, i+1, c)){
                    dbg(i, bs, next);
                    nexts.push_back(next);
                }

            }
        }

        states = nexts;
        // dbg(i, states);
        // print(states[0], i+1, c);
    }

    for(ll state: states){
        bool ok = true;
        for(int j=0; j<c; j++){
            int m = 0;
            for(int l=0; l<r; l++){
                m += state>>(l*c+j)&1;
            }
            if(m!=d[j]) ok = false;
        }
        if(ok){
            cout << "POSSIBLE" << endl;
            print(state, r, c);
            return;
        }
    }

    cout << "IMPOSSIBLE" << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cout << setprecision(20) << fixed;

    // print(48731, 4, 4);
    // dbg(check(48731, 4, 4));
    // return 0;

    int t;
    cin >> t;
    for(int i=0; i<t; i++){
        cout << "Case #" << i+1 << ": ";
        solve();
    }
    return 0;
}