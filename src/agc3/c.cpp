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
	vector<ll> A(N);
	for(int i=0; i<N; i++) cin >> A[i];

	vector<pair<ll, int>> xs(N);
	for(int i=0; i<N; i++) xs[i] = {A[i], i};
	sort(xs.begin(), xs.end());

	vector<int> b(N);
	for(int i=0; i<N; i++) b[xs[i].second] = i;

	int ans = 0;
	for(int i=0; i<N; i+=2){
		if(b[i]%2) ans++;
	}
	cout << ans << endl;
	return 0;
}
