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
	int N; cin >> N;
	vector<int> A(N);
	for(int i=0; i<N; i++) cin >> A[i];

	vector<pair<int, int>> v(N);
	for(int i=0; i<N; i++) v[i] = {A[i], i};
	sort(v.begin(), v.end());

	for(int i=0; i<N; i++){
		cout << v[i].second+1 << (i==N-1?'\n':' ');
	}

	return 0;
}
