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

void solve(){
	ll x, y;
	cin >> x >> y;

	bool fx=false, fy=false;
	if(x<0){
		fx=true;
		x = -x;
	}
	if(y<0){
		fy=true;
		y=-y;
	}

	if((x+y)%2==0){
		cout << "IMPOSSIBLE" << endl;
		return;
	}

	string ans;
	for(int k=0; k<32; k++){
		if(x==0&&y==0) break;
		bool s;
		ll nx=x>>1;
		ll ny=y>>1;
		if(nx==0&&ny==0||nx%2!=ny%2){
			s = true;
		} else{
			s = false;
			if(x%2) nx++;
			else ny++;
		}
		if(x%2){
			if(s!=fx){
				ans+="E";
			} else {
				ans+="W";
			}
		} else {
			if(s!=fy){
				ans+="N";
			} else {
				ans+="S";
			}
		}
		x = nx;
		y = ny;
	}

	cout << ans << endl;
}

int main() {
	ios_base::sync_with_stdio(false);
	int t; cin >> t;
	for(int i=0; i<t; i++){
		cout << "Case #" << i+1 << ": ";
		solve();
	}
	return 0;
}
