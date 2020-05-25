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
#define dbg(...) debug_(__VA_ARGS__);
#else
#define dbg(...) 
#endif

int main() {
	ios_base::sync_with_stdio(false);
	int n, m; cin >> n >> m;
	vector<int> x(n), y(n), a(m);
	for(int i=0; i<n; i++){
		cin >> x[i] >> y[i];
	}
	for(int i=0; i<m; i++) cin >> a[i];

	vector<pair<int, int>> vp;
	for(int i=0; i<n; i++){
		vp.push_back({x[i], i});
	}
	for(int i=0; i<m; i++){
		vp.push_back({a[i], n+i});
	}

	sort(vp.begin(), vp.end());

	int ans = 0;
	priority_queue<int, vector<int>, greater<int>> que;
	for(int i=0; i<n+m; i++){
		while(!que.empty()&&que.top()<vp[i].first) que.pop();
		int j = vp[i].second;
		if(j<n) que.push(y[j]);
		else {
			if(!que.empty()){
				que.pop();
				ans++;
			}
		}
	}

	cout << ans << endl;

	return 0;
}
