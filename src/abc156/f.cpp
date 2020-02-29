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
	int K, Q;
	cin >> K >> Q;
	vector<ll> D(K), N(Q), X(Q), M(Q);
	for(int i=0; i<K; i++) cin >> D[i];
	for(int i=0; i<Q; i++){
		cin >> N[i] >> X[i] >> M[i];
	}

	vector<ll> Dm(K);
	for(int i=0; i<Q; i++){
		for(int j=0; j<K; j++) Dm[j] = D[j]%M[i];

		ll sum = 0;
		ll eq = 0;
		for(int j=0; j<K; j++) sum += Dm[j];
		for(int j=0; j<K; j++){
			if(Dm[j]==0) eq++;
		}
		eq *= (N[i]-1) / K;
		ll total = X[i]%M[i] + sum * ((N[i]-1) / K);
		for(int j=0; j<(N[i]-1)%K; j++){
			total += Dm[j];
			if(Dm[j]==0) eq++;
		}
		ll cnt = total / M[i];
		ll rem = total % M[i];
		debug(sum, total, cnt, rem, eq);

		cout << N[i]-1-cnt-eq << endl;
	}

	return 0;
}
