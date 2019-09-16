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
	int N, M;
	cin >> N >> M;
	vector<ll> A(N);
	for(int i=0; i<N; i++) cin >> A[i];

	priority_queue<ll> que;
	for(int i=0; i<N; i++) que.push(A[i]);

	for(int i=0; i<M; i++){
		ll x = que.top();
		que.pop();
		que.push(x/2);
	}

	ll ans = 0;
	for(int i=0; i<N; i++){
		ans += que.top();
		que.pop();
	}
	cout << ans << endl;

	return 0;
}
