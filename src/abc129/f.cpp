#include<bits/stdc++.h>
#include<boost/variant.hpp>
using namespace std;
typedef long long ll;
typedef vector<boost::variant<bool, ll, int, string, double, char*>> any;
template<typename T> inline void pr(const vector<T> &xs){
	for(int i=0; i<xs.size()-1; i++) cout<<xs[i]<<" ";
	(xs.empty()?cout:(cout<<xs[xs.size()-1]))<<endl;
}
template<typename T> inline void debug(const vector<T> &xs){
#ifdef DEBUG
	pr(xs);
#endif
}

void mul(ll x[3][3], ll y[3][3], ll m, ll r[3][3]){
	for(int i=0; i<3; i++){
		for(int j=0; j<3; j++){
			r[i][j]=0;
			for(int k=0; k<3; k++) r[i][j] += x[i][k]*y[k][j];
			r[i][j]%=m;
		}
	}
}

void pow(ll x[3][3], ll y, ll m, ll r[3][3]){
	if(y==0) {
		for(int i=0; i<3; i++){
			for(int j=0; j<3; j++) r[i][j] = i==j?1:0;
		}
	} else if(y%2){
		ll t[3][3];
		pow(x, y-1, m, t);
		mul(x, t, m, r);
	} else {
		ll t[3][3];
		pow(x, y/2, m, t);
		mul(t, t, m, r);
	}
}

int main(){
	ll L, A, B, M;
	cin >> L >> A >> B >> M;

	ll e10[19];
	e10[0] = 1;
	for(int i=1; i<19; i++) e10[i] = 10*e10[i-1];

	ll start = 0;
	ll ans = 0;
	for(int d=1; d<19; d++){
		if(A+start*B >= e10[d]) continue;
		ll lb = start, ub = L-1;
		ll end;
		if(A+B*ub < e10[d]){
			end = ub;
		} else {
			while(ub-lb>1){
				ll med=(lb+ub)/2;
				if(A+B*med<e10[d]) lb = med;
				else ub = med;
			}
			end = lb;
		}
		ll ld = end-start+1;
		ll x[3][3] = {{e10[d]%M, 1, 0}, {0, 1, 1}, {0, 0, 1}};
		ll y[3][3];
		pow(x, ld, M, y);
		ans = ans*y[0][0]%M+(A+start*B)%M*y[0][1]%M+B%M*y[0][2]%M;
		ans %= M;
		debug(any{d, start, end, ld, A+start*B, A+end*B, ans});
		//for(int i=0; i<3; i++) debug(vector<ll>(y[i], y[i]+3));
		start = end+1;
		if(start >= L) break;
	}
	cout << ans << endl;

	return 0;
}
