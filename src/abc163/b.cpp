#include<bits/stdc++.h>
#include<boost/variant.hpp>
using namespace std;
typedef long long ll;
typedef vector<boost::variant<bool, ll, int, string, double, char*, const char*>> anys;
template<typename T> inline void pr(const vector<T> &xs){
	for(int i=0; i<xs.size()-1; i++) cout<<xs[i]<<" ";
	(xs.empty()?cout:(cout<<xs[xs.size()-1]))<<endl;
}
#ifdef DEBUG
#define debug(...) pr(anys{__VA_ARGS__})
#define debugv(x) pr((x))
#else
#define debug(...)
#define debugv(x)
#endif

int main(){
	int N, M;
	cin >> N >> M;
	vector<int> A(M);
	for(int i=0; i<M; i++) cin >> A[i];

	ll sum = 0;
	for(int i=0; i<M; i++) sum += A[i];

	if(N >= sum){
		cout << N - sum << endl;
	} else {
		cout << -1 << endl;
	}


	return 0;
}
