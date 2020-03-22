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
	vector<int> S(M), C(M);
	for(int i=0; i<M; i++) cin >> S[i] >> C[i];

	for(int x=0; x<1000; x++){
		bool ok = true;
		int c[3];
		if(N==1){
			if(x>=10) continue;
			c[0] = x;
		} else if(N==2){
			if(x<10 || 100<=x) continue;
			c[0] = x/10;
			c[1] = x%10;
		} else {
			if(x<100) continue;
			c[0] = x/100;
			c[1] = (x/10)%10;
			c[2] = x%10;
		}

		for(int i=0; i<M; i++){
			if(c[S[i]-1]!=C[i]) ok = false;
		}
		if(ok){
			cout << x << endl;
			return 0;
		}
	}

	cout << -1 << endl;
	return 0;
}
