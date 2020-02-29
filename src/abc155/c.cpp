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
	int N;
	cin >> N;
	vector<string> S(N);
	for(int i=0; i<N; i++) cin >> S[i];

	map<string, int> cnt;
	for(int i=0; i<N; i++) cnt[S[i]]++;

	int n_max = 0;
	for(auto p: cnt){
		n_max = max(n_max, p.second);
	}

	for(auto p: cnt){
		if(p.second==n_max) cout << p.first << endl;
	}

	return 0;
}
