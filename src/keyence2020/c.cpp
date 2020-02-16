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
	int N, K;
	cin >> N >> K;
	ll S;
	cin >> S;

	vector<ll> ans;
	if(S > N){
		for(int i=0; i<K; i++) ans.push_back(S);
		for(int i=K; i<N; i++) ans.push_back(1);
	} else {
		for(int i=0; i<K; i++) ans.push_back(S);
		for(int i=K; i<N; i++) ans.push_back(1e9);
	}

	pr(ans);

	return 0;
}
