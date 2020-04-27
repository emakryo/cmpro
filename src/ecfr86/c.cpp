#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

#ifdef DBG
#define dbg(...) printf(__VA_ARGS__);
#else
#define dbg(...)
#endif

void solve(){
    int A, B, Q;
    cin >> A >> B >> Q;

    vector<int> cum(A*B);
    for(int i=1; i<A*B; i++){
        cum[i] = cum[i-1];
        if(i%A%B!=i%B%A) cum[i]++;
    }

    for(int i=0; i<Q; i++){
        ll l, r;
        cin >> l >> r;
        l--;
        ll x = cum[r%(A*B)] + r/(A*B)*cum[A*B-1];
        ll y = cum[l%(A*B)] + l/(A*B)*cum[A*B-1];
        cout << x - y;
        if(i==Q-1) cout << endl;
        else cout << " ";
    }
}

int main() {
    int T;
    cin >> T;
    for(int i=0; i<T; i++){
        solve();
    }
	return 0;
}
