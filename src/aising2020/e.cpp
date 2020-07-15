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

template<typename T>
istream& operator>>(istream &is, vector<T> &v){
	for(int i=0; i<v.size(); i++) is >> v[i];
	return is;
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

void solve(){
	int n; cin >> n;
	vector<int> k(n);
	vector<ll> l(n), r(n);
	for(int i=0; i<n; i++){
		cin >> k[i] >> l[i] >> r[i];
	}

	ll ans = 0;
	vector<pair<int, ll>> ls, rs;
	for(int i=0; i<n; i++){
		if(l[i]<r[i]){
			ans += l[i];
			rs.push_back({n-k[i], r[i]-l[i]});
		}else if(r[i]<l[i]){
			ans += r[i];
			ls.push_back({k[i], l[i]-r[i]});
		}else{
			ans += l[i];
		}
	}

	sort(ls.rbegin(), ls.rend());
	sort(rs.rbegin(), rs.rend());

	priority_queue<ll> lque;
	int j=0;
	for(int i=ls.size()-1; i>=0; i--){
		while(j<ls.size()&&i<ls[j].first){
			dbg(i, j, ls[j].first, ls[j].second);
			lque.push(ls[j].second);
			j++;
		}
		if(lque.size()){
			dbg("l", lque.top());
			ans += lque.top();
			lque.pop();
		}
	}

	j=0;
	priority_queue<ll> rque;
	for(int i=rs.size()-1; i>=0; i--){
		while(j<rs.size()&&i<rs[j].first){
			dbg(i, j, rs[j].first, rs[j].second);
			rque.push(rs[j].second);
			j++;
		}
		if(rque.size()){
			dbg("r", rque.top());
			ans += rque.top();
			rque.pop();
		}
	}

	cout << ans << endl;
}

int main() {
	ios_base::sync_with_stdio(false);
	cout << setprecision(20) << fixed;

	int t; cin >> t;
	for(int i=0; i<t; i++) solve();
	return 0;
}
