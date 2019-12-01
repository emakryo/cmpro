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
	string S;
	cin >> N >> S;

	vector<int> idx[10];
	for(int i=0; i<N; i++){
		idx[S[i]-'0'].push_back(i);
	}

	int ans = 0;
	for(int i=0; i<1000; i++){
		int a = i/100;
		int b = (i/10)%10;
		int c = i%10;
		if(idx[a].size()==0) continue;
		int ia = idx[a][0];
		auto ib = lower_bound(idx[b].begin(), idx[b].end(), ia+1);
		if(ib == idx[b].end()) continue;
		auto ic = lower_bound(idx[c].begin(), idx[c].end(), *ib+1);
		if(ic == idx[c].end()) continue;
		ans++;
	}

	cout << ans << endl;

	return 0;
}
