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
	int N, Z, W;
	cin >> N >> Z >> W;
	vector<int> A(N);
	for(int i=0; i<N; i++) cin >> A[i];

	if(N>=2) cout << max(abs(A[N-1]-W), abs(A[N-1]-A[N-2])) << endl;
	else cout << abs(A[N-1]-W) << endl;

	return 0;
}
