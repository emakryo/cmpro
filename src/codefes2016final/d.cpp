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
	int N, M;
	cin >> N >> M;
	vector<int> X(N);
	for(int i=0; i<N; i++) cin >> X[i];

	sort(X.begin(), X.end());

	bool mark = false;
	vector<int> cnt(M), pair(M);
	for(int i=0; i<N; i++){
		cnt[X[i]%M]++;
		if(i<N-1&&X[i]==X[i+1]&&!mark){
			pair[X[i]%M]++;
			mark = true;
		} else {
			mark = false;
		}
	}

	ll ans = 0;
	for(int i=1; i<(M+1)/2; i++){
		debug(cnt[i], cnt[M-i]);
		int x = min(cnt[i], cnt[M-i]);
		ans += x;
		ans += min(max(0, cnt[i]-x)/2, pair[i]);
		ans += min(max(0, cnt[M-i]-x)/2, pair[M-i]);
	}
	ans += cnt[0]/2;
	if(M%2==0) ans += cnt[M/2]/2;
	cout << ans << endl;

	return 0;
}
