#include<iostream>
#include<iomanip>
//#include<cstdio>
#include<vector>
#include<map>
#include<queue>
#include<algorithm>
#include<cmath>
#include<cassert>
using namespace std;
typedef long long ll;

int main(){
    ll N;
    cin >> N;

    ll ans = 0;
    for(ll p=1; p*p<N; p++){
        if(N%p==0) {
            ll q = N/p;
            //cout << p << " " << q << endl;
            ll m = p-1;
            ll y = q;
            if(y < m) ans += m;
            m = q-1;
            y = p;
            if(y < m) ans += m;
        }
    }

    cout << ans << endl;

	return 0;
}
