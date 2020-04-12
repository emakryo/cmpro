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
	ll N;
	cin >> N;

	pair<ll, ll> win, lose;
	lose = {(N+2)/2, N};
	while(true){
		debug("lose", lose.first, lose.second);
		if(lose.first <= 1 && 1 <= lose.second){
			cout << "Aoki" << endl;
			return 0;
		}
		win = {lose.first/2, lose.first-1};
		debug("win", win.first, win.second);
		if(win.first <= 1 && 1 <= win.second){
			cout << "Takahashi" << endl;
			return 0;
		}
		lose = {(win.first+1)/2, win.first-1};
	}

	return 0;
}
