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
	ios_base::sync_with_stdio(false);

	int H, W, N;
	cin >> H >> W >> N;
	vector<pair<int, int>> RC(N);
	for(int i=0; i<N; i++){
		cin >> RC[i].first >> RC[i].second;
		RC[i].first--;
		RC[i].second--;
	}

	vector<vector<int>> cs(H);
	for(int i=0; i<N; i++) cs[RC[i].first].push_back(RC[i].second);
	for(int i=0; i<H; i++) sort(cs[i].begin(), cs[i].end());

	int ans = 0;
	for(int r0=0; r0<H; r0++){
		set<int> cst;
		for(int r1=r0; r1<H; r1++){
			for(int c: cs[r1]) cst.insert(c);
			if(r0>0&&cs[r0-1].size()==0) continue;
			if(r1<H-1&&cs[r1+1].size()==0) continue;

			int c0 = 0;
			int r0_c_min = r0 > 0 ? cs[r0-1][0] : 0;
			int r1_c_min = r1 < H-1 ? cs[r1+1][0] : 0;
			int r0_c_max = r0 > 0 ? cs[r0-1][cs[r0-1].size()-1] : W-1;
			int r1_c_max = r1 < H-1 ? cs[r1+1][cs[r1+1].size()-1] : W-1;
			int c_min = min(r0_c_min, r1_c_min);
			int c_max = max(r0_c_max, r1_c_max);

			for(auto p = cst.lower_bound(c_min); p!=cst.end()&&*p<=c_max; p++){
				int c1 = *p;
				debug(r0, r1, c1);
				if(c1-c0<1){
					c0 = c1+1;
					continue;
				}
				c1--;
				bool ok_r0 = true;
				if(r0>0){
					auto it = lower_bound(cs[r0-1].begin(), cs[r0-1].end(), c0);
					ok_r0 = it != cs[r0-1].end() && *it <= c1;
				}
				bool ok_r1 = true;
				if(r1<H-1){
					auto it = lower_bound(cs[r1+1].begin(), cs[r1+1].end(), c0);
					ok_r1 = it != cs[r1+1].end() && *it <= c1;
				}
				debug(r0, r1, c0, c1, ok_r0, ok_r1);
				if(ok_r0&&ok_r1){
					ans++;
				}
				c0 = c1+2;
			}
			int c1 = W-1;
			if(c1-c0>=0){
				bool ok_r0 = true;
				if(r0>0){
					auto it = lower_bound(cs[r0-1].begin(), cs[r0-1].end(), c0);
					ok_r0 = it != cs[r0-1].end() && *it <= c1;
				}
				bool ok_r1 = true;
				if(r1<H-1){
					auto it = lower_bound(cs[r1+1].begin(), cs[r1+1].end(), c0);
					ok_r1 = it != cs[r1+1].end() && *it <= c1;
				}
				debug(r0, r1, c0, c1, ok_r0, ok_r1);
				if(ok_r0&&ok_r1){
					ans++;
				}
			}
		}
	}

	cout << ans << endl;
	return 0;
}
