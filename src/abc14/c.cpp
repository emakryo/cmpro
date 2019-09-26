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
	int N;
	cin >> N;
	vector<int> A(N), B(N);
	for(int i=0; i<N; i++) cin >> A[i] >> B[i];
	vector<int> X(1000001), Y(1000001);
	for(int i=0; i<N; i++){
		X[A[i]]++;
		Y[B[i]]++;
	}

	int ans = 0;
	int cur = 0;
	for(int i=0; i<1000001; i++){
		cur += X[i];
		ans = max(ans, cur);
		cur -= Y[i];
	}
	cout << ans << endl;


	return 0;
}
