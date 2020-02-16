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
	int N, K, M;
	cin >> N >> K >> M;
	vector<int> A(N-1);
	for(int i=0; i<N-1; i++) cin >> A[i];

	int sum = 0;
	for(int i=0; i<N-1; i++) sum += A[i];
	int x = N*M - sum;
	if(x <= K) cout << max(0, x) << endl;
	else cout << -1 << endl;

	return 0;
}
