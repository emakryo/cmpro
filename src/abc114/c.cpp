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

int main(){
	ll N;
	cin >> N;
	vector<ll> xs = {3, 5, 7};
	vector<ll> ys;

	for(int k=0; k<9; k++){
		vector<ll> next;
		int n=xs.size();
		for(int i=0; i<n; i++){
			next.push_back(10*xs[i]+3);
			next.push_back(10*xs[i]+5);
			next.push_back(10*xs[i]+7);
		}
		if(k>0){
			for(int x: next) ys.push_back(x);
		}
		xs = next;
	}
	debug(any{(int)xs.size()});

	int ans = 0;
	for(ll x: ys){
		if(x<100||N<x) continue;
		bool p3 = false, p5 = false, p7 = false;
		ll y = x;
		while(x>0){
			p3 = p3 || x%10==3;
			p5 = p5 || x%10==5;
			p7 = p7 || x%10==7;
			x /= 10;
		}
		if(p3&&p5&&p7){
			ans++;
			debug(any{y});
		}
	}
	cout << ans << endl;


	return 0;
}
