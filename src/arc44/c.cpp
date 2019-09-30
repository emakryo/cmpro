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

ll solve(int w, vector<pair<int, int>> &beam){
	int n = beam.size();
	sort(beam.begin(), beam.end());
	vector<int> left(n), right(n);
	for(int i=0; i<n; i++){
		if(i>0&&beam[i-1].first==beam[i].first&&beam[i-1].second==beam[i].second-1){
			left[i] = left[i-1];
		} else {
			left[i] = beam[i].second-1;
		}
	}
	for(int i=n-1; i>=0; i--){
		if(i<n-1&&beam[i+1].first==beam[i].first&&beam[i+1].second==beam[i].second+1){
			right[i] = right[i+1];
		} else {
			right[i] = beam[i].second+1;
		}
	}
	debug(left);
	debug(right);
	vector<ll> cnt(w);
	map<int, ll> update;
	int t = 0;
	for(int i=0; i<n; i++) {
		if(left[i] < 0 && w <= right[i]) {
			return -1;
		}
		ll l = left[i] >=0 ? cnt[left[i]] + abs(beam[i].second-left[i]) : 1e18;
		ll r = right[i] < w ? cnt[right[i]] + abs(beam[i].second-right[i]) : 1e18;
		update[beam[i].second] = min(l, r);
		if(i==n-1||beam[i+1].first != t){
			for(auto p: update){
				cnt[p.first] = p.second;
			}
			t = beam[i+1].first;
			update.clear();
		}
	}

	ll ret = cnt[0];
	for(int i=0; i<w; i++){
		ret = min(ret, cnt[i]);
	}
	debug(any{ret});
	return ret;
}

int main(){
	int W, H, Q;
	cin >> W >> H >> Q;
	vector<pair<int, int>> Bv, Bh;
	for(int i=0; i<Q; i++){
		int t, d, x;
		cin >> t >> d >> x;
		if(d==0) Bv.push_back({t, x-1});
		else Bh.push_back({t, x-1});
	}

	ll a1 = solve(W, Bv);
	ll a2 = solve(H, Bh);
	if(a1 < 0 || a2 < 0) cout << -1 << endl;
	else cout << a1 + a2 << endl;

	return 0;
}
