#include<bits/stdc++.h>
#include<boost/variant.hpp>
using namespace std;
typedef long long ll;
typedef vector<boost::variant<bool, ll, int, string, double>> any;
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

	vector<int> A(N);
	for(int i=0; i<N; i++) cin >> A[i];


	ll cur = 0;
	int cnt = 0;
	for(int i=1; i<N; i++){
		if(A[i-1] < A[i]){
			cur += A[i]-A[i-1];
		} else {
			cnt++;
			cur += A[i];
		}
	}

	vector<ll> c(M+1);
	for(int i=1; i<N; i++){
		c[A[i]] += (A[i]-A[i-1]+M)%M-1;
	}

	vector<int> b(M+1), d(M+1);
	for(int i=0; i<N-1; i++) b[A[i]]++;
	for(int i=1; i<N; i++) d[A[i]]++;

	ll ans = cur;
	debug(any{cur});
	for(int x=1; x<M; x++){
		cnt -= d[x];
		cur -= cnt;
		cur += c[x];
		ans = min(ans, cur);
		debug(any{x, cur, cnt, d[x], b[x], c[x]});
		cnt += b[x];
	}

	cout << ans << endl;

	return 0;
}
