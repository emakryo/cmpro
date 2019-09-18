#include<bits/stdc++.h>
#include<boost/variant.hpp>
using namespace std;
typedef long long ll;
typedef vector<boost::variant<bool, ll, int, string, double, char*, const char*>> any;
template<typename T> inline void pr(const vector<T> &xs){
	for(int i=0; i<xs.size()-1; i++) cout<<xs[i]<<" ";
	(xs.empty()?cout:(cout<<xs[xs.size()-1]))<<endl;
}
template<typename T> inline void debug(const vector<T> &xs){
#ifdef DEBUG
	pr(xs);
#endif
}

int main(){
	int D, G;
	cin >> D >> G;
	vector<int> P(D), C(D);
	for(int i=0; i<D; i++) cin >> P[i] >> C[i];

	int ans = 1e9;
	for(int k=0; k<1<<D; k++){
		int x = 0;
		int n = 0;
		for(int d=D-1; d>=0; d--){
			if((k>>d)&1){
				x += 100*(d+1)*P[d] + C[d];
				n += P[d];
			}
		}
		debug(any({k, x, n}));
		if(x>=G){
			ans = min(ans, n);
			continue;
		}
		int d=D-1;
		while((k>>d)&1) d--;
		if(d<0) continue;
		int l = (G-x+100*(d+1)-1)/(100*(d+1));
		if(0<=l&&l<P[d]) ans = min(ans, n+l);
	}
	cout << ans << endl;

	return 0;
}
