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
const int Amax = 1e5;
int A, B, Q;
ll S[Amax], T[Amax], X[Amax];

int main(){
	cin >> A >> B >> Q;
	for(int i=0; i<A; i++) cin >> S[i];
	for(int i=0; i<B; i++) cin >> T[i];
	for(int i=0; i<Q; i++){
		cin >> X[i];

		int si = lower_bound(S, S+A, X[i])-S;
		int ti = lower_bound(T, T+B, X[i])-T;

		ll ans = 1e18;
		if(si < A && ti < B) ans = min(ans, max(S[si]-X[i], T[ti]-X[i]));
		if(si > 0 && ti > 0) ans = min(ans, max(X[i]-S[si-1], X[i]-T[ti-1]));
		if(si > 0 && ti < B){
			ans = min(ans, 2*(X[i]-S[si-1])+T[ti]-X[i]);
			ans = min(ans, X[i]-S[si-1]+2*(T[ti]-X[i]));
		}
		if(si < A && ti > 0){
			ans = min(ans, 2*(S[si]-X[i])+X[i]-T[ti-1]);
			ans = min(ans, S[si]-X[i]+2*(X[i]-T[ti-1]));
		}
		cout << ans << endl;
	}

	return 0;
}
