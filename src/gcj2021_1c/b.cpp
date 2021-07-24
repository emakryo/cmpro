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

bool check(ll x){
    vector<ll> d(18, 1);
    for(int i=1; i<18; i++) d[i] = 10*d[i-1];

    for(int i=1; i<18; i++){
        ll x0 = x/d[i];
        if(x0==0) break;

        string xs = to_string(x0);
        while(xs.size()<=18){
            if(atoll(xs.c_str())==x) return true;
            xs += to_string(++x0);
        }
    }

    return false;
}

__int128_t parse(string &s) {
  ll ret = 0;
  for (int i = 0; i < s.length(); i++)
    if ('0' <= s[i] && s[i] <= '9')
      ret = 10 * ret + s[i] - '0';
  return ret;
}

std::ostream &operator<<(std::ostream &dest, __int128_t value) {
  std::ostream::sentry s(dest);
  if (s) {
    __uint128_t tmp = value < 0 ? -value : value;
    char buffer[128];
    char *d = std::end(buffer);
    do {
      --d;
      *d = "0123456789"[tmp % 10];
      tmp /= 10;
    } while (tmp != 0);
    if (value < 0) {
      --d;
      *d = '-';
    }
    int len = std::end(buffer) - d;
    if (dest.rdbuf()->sputn(d, len) != len) {
      dest.setstate(std::ios_base::badbit);
    }
  }
  return dest;
}

void solve_easy() {
    ll y;
    cin >> y;
    vector<ll> d(18, 1);
    for(int i=1; i<18; i++) d[i] = 10*d[i-1];

    for(int x=y+1; x<1e7; x++){
        if(check(x)){
            cout << x << endl;
            return;
        }
    }
}

__int128_t gen(ll x, int k) {
    string r;
    for(int i=0; i<k; i++){
        r += to_string(x);
    }
    if(r.size()>=20){
        return -1;
    } else {
        return parse(r);
    }
}

void solve(){
    ll y;
    cin >> y;
    vector<ll> d(18, 1);
    for(int i=1; i<18; i++) d[i] = 10*d[i-1];

    __int128_t ans = 2e18;

    for(int i=1; i<12; i++){
        for(int k=2; k<15; k++){
            for(int l=1; l<30; l++){
                if(d[i]-l>0){
                    __int128_t z = gen(d[i]-l, k);
                    if(z>y) ans = min(ans, z);
                }
            }
        }
    }

    for(int i=1; i<18; i++){
        ll x = y/d[i];
        for(int k=2; k<15; k++){
            __int128_t z = gen(x, k);
            if(z>y) ans = min(ans, z);
            z = gen(x+1, k);
            if(z>y) ans = min(ans, z);
        }
    }

    cout << ans << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cout << setprecision(20) << fixed;

    int t;
    cin >> t;
    for(int i=0; i<t; i++){
        cout << "Case #" << i+1 << ": ";
        solve_easy();
    }
    return 0;
}