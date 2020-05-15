#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

template<typename T>
ostream& operator<<(ostream &os, vector<T> &v){
	string sep = " ";
	if(v.size()) os << v[0];
	for(int i=1; i<v.size(); i++) os << sep << v[i];
	return os;
}

#ifdef DBG
void debug_(){ cout << endl; }
template<typename T, typename... Args>
void debug_(T&& x, Args&&... xs){
	cout << x << " "; debug_(forward<Args>(xs)...);
}
#define dbg(...) debug_(__VA_ARGS__)
#else
#define dbg(...) 
#endif

int main() {
	ios_base::sync_with_stdio(false);
	int r, c, k;
	cin >> r >> c >> k;
	int n; cin >> n;
	vector<int> xs(n), ys(n);
	for(int i=0; i<n; i++) cin >> xs[i] >> ys[i];

	map<int ,vector<int>> xy, yx;
	for(int i=0; i<n; i++){
		xy[xs[i]].push_back(ys[i]);
		yx[ys[i]].push_back(xs[i]);
	}

	vector<int> ny;
	for(int y=0; y<c; y++){
		ny.push_back(yx[y+1].size());
	}
	sort(ny.begin(), ny.end());

	ll ans = 0;
	for(int x=1; x<=r; x++){
		int l = k-xy[x].size();
		if(l<0) continue;
		int m = upper_bound(ny.begin(), ny.end(), l) - lower_bound(ny.begin(), ny.end(), l);
		for(int y: xy[x]){
			dbg(y, yx[y].size());
			if(yx[y].size()==l){
				m--;
			}
			if(yx[y].size()==l+1){
				m++;
			}
		}
		dbg(x, l, m);
		ans += m;
	}

	cout << ans << endl;

	return 0;
}
