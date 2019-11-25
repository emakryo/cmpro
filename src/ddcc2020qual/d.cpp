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
	int M;
	cin >> M;
	vector<pair<int, ll>> dc(M);
	for(int i=0; i<M; i++) cin >> dc[i].first >> dc[i].second;

	vector<int> rev;
	ll ans = 0;
	while(dc.size()>0){
		int d = dc[dc.size()-1].first;
		ll c = dc[dc.size()-1].second;
		dc.pop_back();
		if(c == 1){
			rev.push_back(d);
			continue;
		}
		if(c%2){
			rev.push_back(d);
			c--;
		}
		c /= 2;
		d = 2*d;
		ans += c;
		if(d>=10){
			d -= 9;
			ans += c;
		}
		dc.push_back({d, c});
	}

	debugv(rev);
	debug(ans);

	while(rev.size()>1){
		int d1 = rev[rev.size()-1];
		rev.pop_back();
		int d2 = rev[rev.size()-1];
		rev.pop_back();
		int d = d1+d2;
		ans++;
		rev.push_back(d%10);
		if(d>=10){
			rev.push_back(1);
		}
	}
	cout << ans << endl;

	return 0;
}
