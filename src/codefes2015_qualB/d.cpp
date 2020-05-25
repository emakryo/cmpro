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
	int n; cin >> n;
	vector<ll> s(n), c(n);
	for(int i=0; i<n; i++) cin >> s[i] >> c[i];

	map<ll, ll> range;
	for(int i=0; i<n; i++){
		auto next = range.lower_bound(s[i]);
		vector<ll> dels;
		ll left = s[i];
		while(next != range.end()){
			if(s[i]+c[i]-1<next->second){
				break;
			} else if(s[i]<next->second){
				c[i] -= next->second-s[i];
				next->second = s[i];
			}
			left = min(left, next->second);
			s[i] = next->first+1;
			dbg(i, s[i], c[i], next->first, next->second);
			dels.push_back(next->first);
			next++;
		}
		range[s[i]+c[i]-1] = left;
		dbg(i, s[i], c[i], left, s[i]+c[i]-1);
		cout << s[i]+c[i]-1 << endl;
		for(ll d: dels){
			range.erase(d);
		}
	}

	return 0;
}
