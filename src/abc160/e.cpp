#include<bits/stdc++.h>
#include<boost/variant.hpp>
using namespace std;
typedef long long ll;
typedef vector<boost::variant<bool, ll, int, string, double, char*, const char*>> any;
template<typename T> inline void pr(const vector<T> &xs){
	for(int i=0; i<xs.size()-1; i++) cout<<xs[i]<<" ";
	(xs.empty()?cout:(cout<<xs[xs.size()-1]))<<endl;
}
#ifdef DEBUG
#define debug(...) pr(any{__VA_ARGS__})
#define debugv(x) pr((x))
#else
#define debug(...)
#define debugv(x)
#endif

int main(){
	int X, Y, A, B, C;
	cin >> X >> Y >> A >> B >> C;
	vector<ll> P(A), Q(B), R(C);
	for(int i=0; i<A; i++) cin >> P[i];
	for(int i=0; i<B; i++) cin >> Q[i];
	for(int i=0; i<C; i++) cin >> R[i];

	vector<pair<ll, int>> xs(A+B+C);
	for(int i=0; i<A; i++) xs[i]={P[i], 0};
	for(int i=0; i<B; i++) xs[i+A]={Q[i], 1};
	for(int i=0; i<C; i++) xs[i+A+B]={R[i], 2};

	sort(xs.begin(), xs.end());
	reverse(xs.begin(), xs.end());

	ll ans = 0;
	int na=0, nb=0, nc=0;
	for(int i=0; i<xs.size(); i++){
		ll x = xs[i].first;
		ll t = xs[i].second;
		debug(i, x, t);
		if(t==0 && na<X){
			ans += x;
			na++;
		} else if(t==1 && nb<Y){
			ans += x;
			nb++;
		} else if(t==2 && na+nb+nc<X+Y){
			ans += x;
			nc++;
		}
		if(na+nb+nc==X+Y) break;
	}
	cout << ans << endl;

	return 0;
}
