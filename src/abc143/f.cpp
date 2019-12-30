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
	cin >> N;
	vector<int> A(N);
	for(int i=0; i<N; i++) cin >> A[i];

	vector<int> count(N+1);
	for(int i=0; i<N; i++) count[A[i]]++;
	vector<int> b;
	for(int i=0; i<N+1; i++) if(count[i]>0) b.push_back(count[i]);
	sort(b.begin(), b.end());

	vector<ll> xs;
	int k = 0;
	ll sum = 0;
	int c = 0;
	for(ll x=0; x<=N; x++){
		while(b[k]==x){
			k++;
			c++;
			sum += x;
		}
		xs.push_back(sum + (b.size()-c) * x);
		debug(x, c, sum, (ll)(sum+(b.size()-c)*x));
	}

	for(int i=1; i<=N; i++){
		int lb=0, ub=N+1;
		while(ub-lb>1){
			ll x = (ub+lb)/2;
			if(i*x<=xs[x]){
				lb = x;
			} else {
				ub = x;
			}
		}
		cout << lb << endl;
	}

	return 0;
}
