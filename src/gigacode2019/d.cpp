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
	int H, W;
	ll K, V;
	cin >> H >> W >> K >> V;
	vector<vector<ll>> A(H, vector<ll>(W));
	for(int i=0; i<H; i++){
		for(int j=0; j<W; j++) cin >> A[i][j];
	}

	vector<vector<ll>> cum(H+1, vector<ll>(W+1));
	for(int i=0; i<H; i++){
		for(int j=0; j<W; j++){
			cum[i+1][j+1] = A[i][j] + cum[i+1][j] + cum[i][j+1] - cum[i][j];
		}
	}

	int ans = 0;
	for(int h0=0; h0<H; h0++){
		for(int w0=0; w0<W; w0++){
			for(int h1=h0+1; h1<=H; h1++){
				ll cost = cum[h1][W]-cum[h1][w0]-cum[h0][W]+cum[h0][w0]+K*(h1-h0)*(W-w0);
				if(cost<=V){
					debug(h0, h1, w0, W, cost);
					ans = max((h1-h0)*(W-w0), ans);
					continue;
				}
				int lb = w0, ub = W;
				while(ub-lb>1){
					int w1 = (lb+ub)/2;
					ll cost = cum[h1][w1]-cum[h1][w0]-cum[h0][w1]+cum[h0][w0]+K*(h1-h0)*(w1-w0);
					if(cost <= V){
						lb = w1;
					} else {
						ub = w1;
					}
				}
				cost = cum[h1][lb]-cum[h1][w0]-cum[h0][lb]+cum[h0][w0]+K*(h1-h0)*(lb-w0);
				debug(h0, h1, w0, lb, cost);
				ans = max((h1-h0)*(lb-w0), ans);
			}
		}
	}
	cout << ans << endl;



	return 0;
}
