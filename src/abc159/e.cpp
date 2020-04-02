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
	int H, W, K;
	cin >> H >> W >> K;
	vector<string> S(H);
	for(int i=0; i<H; i++) cin >> S[i];

	int ans = 10000000;
	for(int k=0; k<(1<<(H-1)); k++){
		int cnt = 0;
		int nbit = 0;
		bool ng = false;
		for(int j=0; j<H; j++) nbit += (k>>j)&1;
		debug(k, nbit);
		vector<int> xs(nbit+1), ys(nbit+1);
		for(int i=0; i<W; i++){
			int p = 0;
			int s = 0;
			for(int j=0; j<H; j++){
				if(S[j][i]=='1') s++;
				if((k>>j)&1){
					ys[p] = s;
					p++; s=0;
				}
			}
			ys[p] = s;

			debug(i, k);
			debugv(ys);

			bool cut = false;
			for(int j=0; j<=nbit; j++){
				if(xs[j]+ys[j] > K) cut = true;
				if(ys[j]>K) ng = true;
			}
			if(cut){
				for(int j=0; j<=nbit; j++) xs[j] = ys[j];
				cnt++;
			} else {
				for(int j=0; j<=nbit; j++) xs[j] += ys[j];
			}
		}
		debug("cnt", k, cnt);
		if(ng) continue;
		ans = min(ans, nbit+cnt);
	}

	cout << ans << endl;

	return 0;
}
