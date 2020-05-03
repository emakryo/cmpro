#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

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
	ll X;
	cin >> X;

	ll a = 100;
	for(int i=0; i<100000; i++){
		a = ll(a*1.01);
		if(a>=X){
			cout << i+1 << endl;
			return 0;
		}
	}
	return 0;
}
