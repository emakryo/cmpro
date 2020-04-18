#include<bits/stdc++.h>
#include<boost/variant.hpp>
using namespace std;
typedef long long ll;
typedef vector<boost::variant<bool, ll, int, string, double, char*, const char*>> anys;
template<typename T> inline void pr(const vector<T> &xs){
	for(int i=0; i<xs.size()-1; i++) cout<<xs[i]<<" ";
	(xs.empty()?cout:(cout<<xs[xs.size()-1]))<<endl;
}
#ifdef DEBUG
#define debug(...) pr(anys{__VA_ARGS__})
#define debugv(x) pr((x))
#else
#define debug(...)
#define debugv(x)
#endif

int main(){
	int N;
	cin >> N;
	vector<ll> A(N), B(N);
	for(int i=0; i<N; i++) cin >> A[i];
	for(int i=0; i<N; i++) cin >> B[i];

	priority_queue<pair<ll, int>> que;
	for(int i=0; i<N; i++) que.push({B[i], i});

	ll ans = 0;
	while(!que.empty()){
		ll x = que.top().first;
		int n = que.top().second;
		que.pop();

		ll y = max(A[n], max(B[(n-1+N)%N], B[(n+1)%N]));
		ll z = B[(n-1+N)%N] + B[(n+1)%N];
		ll k = (x - y + z - 1) / z;
		ans += k;
		B[n] -= k * z;
		debug(n, x, B[n]);

		if(x - k * z < A[n]) {
			cout << -1 << endl;
			return 0;
		}
		if(x - k * z > A[n]) {
			que.push({B[n], n});
		}
	}
	cout << ans << endl;

	return 0;
}
