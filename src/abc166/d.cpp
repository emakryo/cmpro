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
	for(ll a=-1000; a<=1000; a++){
		for(ll b=-1000; b<=1000; b++){
			if(a*a*a*a*a-b*b*b*b*b==X){
				cout << a << " " << b << endl;
				return 0;
			}
		}
	}

	return 0;
}
