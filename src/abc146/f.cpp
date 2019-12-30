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
	int N, M;
	cin >> N >> M;
	string S;
	cin >> S;

	vector<int> next(N+1);
	for(int i=0; i<N+1; i++) next[i] = i;
	int last = N;
	for(int i=N-1; i>=0; i--){
		if(S[i]=='0'){
			last = i;
		} else {
			next[i] = last;
		}
	}

	vector<int> v(N+1);
	for(int i=1; i<=min(N, M); i++){
		if(S[i]=='0') v[i] = i;
	}
	for(int i=M+1; i<=N; i++){
		int n = next[i-M];
		v[i] = i-n;
	}

	vector<int> ans;
	int k = N;
	while(k>0){
		if(v[k]==0){
			cout << -1 << endl;
			return 0;
		}
		ans.push_back(v[k]);
		k -= v[k];
	}
	reverse(ans.begin(), ans.end());

	for(int i=0; i<ans.size(); i++){
		cout << ans[i] << (i==ans.size()-1?'\n':' ');
	}

	return 0;
}
