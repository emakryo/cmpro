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

int dfs(int u, vector<vector<int>> &ch){
	vector<int> cnt;

	for(int v: ch[u]){
		cnt.push_back(dfs(v, ch));
	}

	sort(cnt.begin(), cnt.end());

	for(int i=0; i<cnt.size(); i++){
		cnt[i] += cnt.size()-i;
	}

	int m = 0;
	for(int i=0; i<cnt.size(); i++) m = max(m, cnt[i]);
	debug(u+1, m);
	return m;
}


int main(){
	int N;
	cin >> N;
	vector<int> A(N-1);
	for(int i=0; i<N-1; i++){
		cin >> A[i];
		A[i]--;
	}

	vector<vector<int>> ch(N);
	for(int i=0; i<N-1; i++){
		ch[A[i]].push_back(i+1);
	}

	cout << dfs(0, ch) << endl;

	return 0;
}
