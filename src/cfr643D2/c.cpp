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
	ll a, b, c, d;
	cin >> a >> b >> c >> d;

	ll ans = 0;
	for(ll y=max(b, c-b); y<=c; y++){
		ll p = (y+b-c+1)*(y+b-c)/2;
		ll q = 0, r = 0, s = 0;
		if(y > c-a+1){
			q = (y+a-c)*(y+a-c-1)/2;
		}
		if(y > d-b+1){
			r = (y+b-d)*(y+b-d-1)/2;
		}
		if(y > c-a+1 && y > d-b+1 && y > d-a+2){
			s = (y-d+a-1)*(y-d+a-2)/2;
		}
		dbg(y, p, q, r, s);
		ans += p-q-r+s;
	}
	cout << ans << endl;

	return 0;
}
