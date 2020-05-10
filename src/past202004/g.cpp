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
	int q; cin >> q;
	deque<pair<string, int>> s;

	for(int i=0; i<q; i++){
		int x; cin >> x;
		if(x==1){
			string c;
			int x;
			cin >> c >> x;
			s.emplace_back(c, x);
		} else {
			int x;
			cin >> x;
			map<string, ll> cnt;
			while(x>0&&s.size()>0){
				string c = s[0].first;
				int k = s[0].second;
				int l = min(x, k);
				cnt[c]+=l;
				x-=l;
				k-=l;
				if(k==0){
					s.pop_front();
				} else {
					s[0].second = k;
				}
			}
			ll ans = 0;
			for(auto p: cnt){
				ans += p.second*p.second;
			}
			cout << ans << endl;
		}
	}


	return 0;
}
