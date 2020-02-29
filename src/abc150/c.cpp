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

int a = 0, b = 0;

int dfs(int n, int &c, vector<int> &p, vector<bool> &used, vector<int> &x){
	if(p.size()==n){
		bool eq = true;
		for(int i=0; i<n; i++){
			if(p[i]!=x[i]) eq = false;
		}
		if(eq) return c;
		else -1;
		c++;
	}
	for(int i=0; i<n; i++){
		if(used[i]) continue;
		p.push_back(i);
		used[i] = true;
		int ret = dfs(n, c, p, used, x);
		p.pop_back();
		used[i] = false;
		if(ret >= 0) return ret;
	}
	return -1;
}

int main(){
	int N;
	cin >> N;
	vector<int> P(N), Q(N);
	for(int i=0; i<N; i++){
		cin >> P[i];
		P[i]--;
	}
	for(int i=0; i<N; i++){
		cin >> Q[i];
		Q[i]--;
	}

	int x = 0;
	vector<int> p;
	vector<bool> used(N);
	int a = dfs(N, x, p, used, P);
	x = 0;
	int b = dfs(N, x, p, used, Q);

	cout << abs(a-b) << endl;

	return 0;
}
