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

ll gcd(ll x, ll y){
	if(y==0) return x;
	else return gcd(y, x%y);
}

int main(){
	int N;
	ll K;
	cin >> N >> K;
	vector<ll> A(N);
	for(int i=0; i<N; i++) cin >> A[i];

	if(N==1) {
		if(A[0] == K) cout << "POSSIBLE" << endl;
		else cout << "IMPOSSIBLE" << endl;
		return 0;
	}
	ll d = gcd(A[0], A[1]);
	for(int i=2; i<N; i++){
		d = gcd(d, A[i]);
	}

	for(int i=0; i<N; i++){
		if(A[i]==K || A[i]>K && (A[i]-K)%d==0){
			cout << "POSSIBLE" << endl;
			return 0;
		}
	}
	cout << "IMPOSSIBLE" << endl;

	return 0;
}
