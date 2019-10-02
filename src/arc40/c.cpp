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

	int ans = 0;
	for(int i=0; i<N; i++){
		int end = N-1;
		while(end>=0&&S[i][end]=='o') end--;
		if(end<0) continue;
		ans++;
		if(i==N-1) continue;
		for(int j=end; j<N; j++) S[i+1][j]='o';
	}

	cout << ans << endl;


	return 0;
}
