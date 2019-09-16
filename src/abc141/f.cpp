#include<bits/stdc++.h>
#include<boost/variant.hpp>
using namespace std;
typedef long long ll;
typedef vector<boost::variant<bool, ll, int, string, double, char*, const char*>> any;
template<typename T> inline void pr(const vector<T> &xs){
	for(int i=0; i<xs.size()-1; i++) cout<<xs[i]<<" ";
	(xs.empty()?cout:(cout<<xs[xs.size()-1]))<<endl;
}
template<typename T> inline void debug(const vector<T> &xs){
#ifdef DEBUG
	pr(xs);
#endif
}

int main(){
	int N;
	cin >> N;
	vector<ll> A(N);
	for(int i=0; i<N; i++) cin >> A[i];

	ll axor = 0;
	ll aor = 0;
	for(int i=0; i<N; i++){
		axor = axor^A[i];
		aor = aor|A[i];
	}

	vector<bool> yet(61);
	ll mask = 0;
	for(int k=0; k<61; k++){
		yet[k] = ((axor>>k)&1)==0 && ((aor>>k)&1)>0;
		if(((axor>>k)&1)==0){
			mask |= aor&(1LL<<k);
		}
	}

	vector<ll> b(N);
	for(int i=0; i<N; i++) b[i] = A[i]&mask;

	int p=0;
	for(int k=60; k>=0; k--){
		int j=-1;
		for(int i=p; i<N; i++){
			if((b[i]>>k)&1){
				j=i;
				break;
			}
		}
		if(j<0) continue;
		for(int i=0; i<N; i++){
			if(i==j) continue;
			if((b[i]>>k)&1) b[i] ^= b[j];
		}
		swap(b[j], b[p++]);
	}

	ll y = 0;
	for(int i=0; i<N; i++) y ^= b[i];
	debug(b);
	debug(any{axor, aor, mask, y});

	ll red = axor|y;
	cout << dec << red + (axor^red) << endl;

	return 0;
}
