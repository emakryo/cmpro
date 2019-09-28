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

	ll ans = 0;
	for(int i=1; i<N-1; i++){
		if(A[i]<A[i-1]&&A[i]<A[i+1]){
			ans += min(A[i-1], A[i+1])-A[i];
			A[i] = min(A[i-1], A[i+1]);
		} else if(A[i]>A[i-1]&&A[i]>A[i+1]){
			ans += A[i]-max(A[i-1], A[i+1]);
			A[i] = max(A[i-1], A[i+1]);
		}
	}

	for(int i=0; i<N-1; i++){
		ans += abs(A[i]-A[i+1]);
	}
	cout << ans << endl;
	return 0;
}
