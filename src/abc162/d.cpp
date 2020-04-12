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
	string S;
	cin >> N;
	cin >> S;

	vector<int> cr(N), cb(N), cg(N);
	for(int i=0; i<N; i++){
		if(i>0){
			cr[i] = cr[i-1];
			cb[i] = cb[i-1];
			cg[i] = cg[i-1];
		}

		if(S[i]=='R') cr[i]++;
		if(S[i]=='G') cg[i]++;
		if(S[i]=='B') cb[i]++;
	}

	ll ans = 0;
	for(int j=1; j<N; j++) for(int k=j+1; k<N; k++){
		if(S[j]=='R'&&S[k]=='G'||S[j]=='G'&&S[k]=='R'){
			ans += cb[j-1];
			if(j-k+j>=0 && S[j-k+j]=='B') ans--;
		}
		if(S[j]=='B'&&S[k]=='G'||S[j]=='G'&&S[k]=='B'){
			ans += cr[j-1];
			if(j-k+j>=0 && S[j-k+j]=='R') ans--;
		}
		if(S[j]=='B'&&S[k]=='R'||S[j]=='R'&&S[k]=='B'){
			ans += cg[j-1];
			if(j-k+j>=0 && S[j-k+j]=='G') ans--;
		}
	}
	cout << ans << endl;

	return 0;
}
