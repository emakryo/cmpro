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

	vector<int> nh(H);
	for(int i=0; i<H; i++){
		for(int j=0; j<W; j++){
			if(S[i][j]=='#') nh[i]++;
		}
	}
	debugv(nh);

	vector<vector<int>> ans(H, vector<int>(W));
	int n = 1;
	vector<int> hs(1, 0);
	int i0 = 0;
	while(nh[i0]==0) i0++;
	for(int i=i0+1; i<H; i++){
		if(nh[i]>0) hs.push_back(i);
	}
	hs.push_back(H);
	for(int i=0; i<hs.size()-1; i++){
		int h0 = hs[i];
		int h1 = hs[i+1];
		debug(h0, h1);

		vector<int> nw(W);
		for(int w=0; w<W; w++){
			for(int h=h0; h<h1; h++){
				if(S[h][w]=='#') nw[w]++;
			}
		}
		vector<int> ws(1, 0);
		int j0 = 0;
		while(nw[j0]==0) j0++;
		for(int w=j0+1; w<W; w++){
			for(int h=h0; h<h1; h++){
				if(S[h][w]=='#'){
					ws.push_back(w);
					break;
				}
			}
		}
		ws.push_back(W);

		for(int j=0; j<ws.size()-1; j++){
			int w0=ws[j];
			int w1=ws[j+1];
			for(int w=w0; w<w1; w++){
				for(int h=h0; h<h1; h++){
					ans[h][w] = n;
				}
			}
			n++;
		}
	}

	for(int i=0; i<H; i++){
		for(int j=0; j<W; j++){
			cout << ans[i][j] << (j==W-1?'\n':' ');
		}
	}

	return 0;
}
