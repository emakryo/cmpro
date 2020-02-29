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

ll gcd(ll x, ll y){
	if(y==0) return x;
	else return gcd(y, x%y);
}

int main(){
	int N; cin >> N;
	ll M; cin >> M;
	vector<ll> A(N);
	for(int i=0; i<N; i++){
		cin >> A[i];
	}

	ll d = A[0]/2;
	for(int i=1; i<N; i++) d = gcd(d, A[i]/2);
	ll g = d;

	for(int i=0; i<N; i++){
		g *= A[i]/2/gcd(g, A[i]/2);
	}
	debug(d, g);

	for(int i=0; i<N; i++){
		if((g / (A[i]/2)) % 2 == 0){
			cout << 0 << endl;
			return 0;
		}
	}

	cout << (M/g + 1)/2 << endl;

	return 0;
}
