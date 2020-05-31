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

void solve(){
	ll h,c, t;
	cin >> h >> c >> t;

	if(t>=h){
		cout << 1 << endl;
		return;
	}

	if(2*t<=(h+c)){
		cout << 2 << endl;
		return;
	}


	ll lb = 0, ub = 1e10;

	while(ub-lb>1){
		ll k = (lb+ub)/2;
		if(h+k*(h+c) < (2*k+1)*t){
			ub = k;
		} else {
			lb = k;
		}
	}
	ll ans = 2;
	double x = abs(t-(h+c)/2.0);

	if(abs(t-h)<x){
		ans = 1;
		x=h;
	}

	for(int i=-2; i<3; i++){
		ll k = max(0ll, lb+i);
		double d = abs(t-(h+k*(h+c))/(2.0*k+1));
		dbg(2*k+1, d, (h+k*(h+c))/(2.0*k+1));
		if(d < x){
			x = d;
			ans = 2*k+1;
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
