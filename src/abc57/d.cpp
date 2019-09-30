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

struct rational {
	ll d, n;
	rational(ll denominator=0, ll nominator=1): d(denominator), n(nominator) {}
	bool operator< (const rational &o) const { return d*o.n<o.d*n; }
	bool operator== (const rational &o) const { return d*o.n==o.d*n; }
	double operator()() const { return (double)d/n; }
};

int main(){
	int N, A, B;
	cin >> N >> A >> B;
	vector<ll> V(N);
	for(int i=0; i<N; i++) cin >> V[i];

	sort(V.begin(), V.end());

	ll sum = 0;
	vector<ll> cnt(N+1);
	vector<rational> mmax(N+1);
	for(int i=0; i<N; i++){
		sum += V[N-i-1];
		int m = i+1;

		if(m<A||B<m) continue;
		auto ub = upper_bound(V.begin(), V.end(), V[N-i-1]);
		auto lb = lower_bound(V.begin(), V.end(), V[N-i-1]);
		int n = ub-lb;
		int k = m - (V.end()-ub);
		k = min(k, n-k);
		ll count = 1;
		for(int j=0; j<k; j++){
			count *= n-j;
			count /= j+1;
		}
		mmax[m] = rational(sum, m);
		cnt[m] = count;
		debug(m, n, k, mmax[m](), cnt[m]);
	}


	rational mans = mmax[A];
	ll cans = cnt[A];
	for(int m=A+1; m<=B; m++){
		if(mans < mmax[m]){
			mans = mmax[m];
			cans = cnt[m];
		} else if(mmax[m] == mans){
			cans += cnt[m];
		}
	}
	cout << setprecision(20) << mans() << endl;
	cout << cans << endl;

	return 0;
}
