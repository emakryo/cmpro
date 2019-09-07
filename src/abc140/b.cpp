#include<bits/stdc++.h>
#include<boost/variant.hpp>
using namespace std;
typedef long long ll;
typedef vector<boost::variant<bool, ll, int, string, double, char*>> any;
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
	int N;
	cin >> N;
	vector<int> A(N), B(N), C(N-1);
	for(int i=0; i<N; i++) cin >> A[i];
	for(int i=0; i<N; i++) cin >> B[i];
	for(int i=0; i<N-1; i++) cin >> C[i];

	ll ans = B[A[0]-1];
	for(int i=1; i<N; i++){
		ans += B[A[i]-1];
		if(A[i]==A[i-1]+1) ans += C[A[i-1]-1];
	}
	cout << ans << endl;

	return 0;
}
