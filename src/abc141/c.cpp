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
	int N, Q;
	ll K;
	cin >> N >> K >> Q;
	vector<int> A(Q);
	for(int i=0; i<Q; i++) cin >> A[i];

	vector<int> x(N);
	for(int i=0; i<Q; i++) x[A[i]-1]++;

	for(int i=0; i<N; i++){
		cout << (K-Q+x[i]>0?"Yes":"No") << endl;
	}

	return 0;
}
