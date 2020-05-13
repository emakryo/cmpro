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
	ll l; cin >> l;
	vector<ll> x(n);
	vector<string> d(n);
	for(int i=0; i<n; i++) cin >> x[i] >> d[i];

	int i=0;
	ll ans = 0;
	while(i<n&&d[i]=="L"){
		ans += x[i]-i-1;
		i++;
	}

	dbg(i, ans);
	while(i<n){
		vector<int> li, ri;
		while(i<n&&d[i]=="R"){
			ri.push_back(i);
			i++;
		}
		while(i<n&&d[i]=="L"){
			li.push_back(i);
			i++;
		}
		dbg(ri, ":", li);
		if(li.size()==0){
			for(int j: ri){
				ans+=l-(n-j-1)-x[j];
			}
		} else {
			int k = ri.back();
			for(int j: ri){
				ans+=x[k]-(k-j)-x[j];
				dbg("r", x[k]-(k-j)-x[j]);
			}
			k = li.front();
			for(int j: li){
				ans+=x[j]-(j-k)-x[k];
				dbg("l", x[j]-(j-k)-x[k]);
			}

			ans += max(ri.size(), li.size()) * (x[li.front()]-x[ri.back()]-1);
		}
	}

	cout << ans << endl;

	return 0;
}
