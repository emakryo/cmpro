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
	int N;
	ll K;
	cin >> N >> K;
	vector<ll> A(N);
	for(int i=0; i<N; i++) cin >> A[i];

	vector<ll> Ap, An;
	int n_0 = 0;
	for(int i=0; i<N; i++){
		if(A[i]>0) Ap.push_back(A[i]);
		if(A[i]<0) An.push_back(A[i]);
		if(A[i]==0) n_0++;
	}
	sort(Ap.begin(), Ap.end());
	sort(An.begin(), An.end());

	if(K<=(ll)Ap.size()*An.size()) {
		ll lb = 0, ub = 1e18+5;
		while(ub-lb>1){
			ll med = (ub+lb)/2;

			ll cnt = 0;
			for(int i=0; i<An.size(); i++){
				auto j = lower_bound(Ap.begin(), Ap.end(), (med-An[i]-1)/(-An[i]));
				cnt += Ap.end() - j;
			}
			debug(med, cnt);

			if(cnt >= K){
				lb = med;
			} else {
				ub = med;
			}
		}
		cout << -lb << endl;
	} else if(K<=(ll)N*(N-1)/2-(ll)An.size()*(An.size()-1)/2-(ll)Ap.size()*(Ap.size()-1)/2){
		cout << 0 << endl;
	} else {
		ll l = K - ((ll)N*(N-1)/2 - (ll)An.size()*(An.size()-1)/2 - (ll)Ap.size()*(Ap.size()-1)/2);
		ll lb = 0, ub = 1e18+5;

		for(int i=0; i<An.size(); i++) An[i] = -An[i];
		sort(An.begin(), An.end());

		while(ub-lb>1){
			ll med = (ub+lb)/2;
			ll cnt = 0;
			for(int i=0; i<An.size(); i++){
				auto j = upper_bound(An.begin()+i+1, An.end(), med/An[i]);
				cnt += j - (An.begin()+i+1);
			}
			for(int i=0; i<Ap.size(); i++){
				auto j = upper_bound(Ap.begin()+i+1, Ap.end(), med/Ap[i]);
				cnt += j - (Ap.begin()+i+1);
			}

			if(cnt < l){
				lb = med;
			} else {
				ub = med;
			}
		}

		cout << ub << endl;
	}

	return 0;
}
