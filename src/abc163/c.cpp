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
	int N;
	cin >> N;
	vector<int> A(N-1);
	for(int i=0; i<N-1; i++) cin >> A[i];

	vector<int> ans(N+1);
	for(int i=0; i<N-1; i++) ans[A[i]]++;

	for(int i=1; i<=N; i++){
		cout << ans[i] << endl;
	}

	return 0;
}
