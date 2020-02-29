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
	vector<int> X(N);
	for(int i=0; i<N; i++){
		cin >> X[i];
	}

	ll ans = 1e9;
	for(int x=1; x<=100; x++){
		ll sum = 0;
		for(int i=0; i<N; i++) sum += (X[i]-x)*(X[i]-x);
		ans = min(ans, sum);
	}

	cout << ans << endl;

	return 0;
}
