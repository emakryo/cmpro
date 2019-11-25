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
	int x, y;
	cin >> x >> y;
	int ans = 0;
	if(x==1){
		ans += 300000;
	} else if(x==2){
		ans += 200000;
	} else if(x==3){
		ans += 100000;
	}
	if(y==1){
		ans += 300000;
	} else if(y==2){
		ans += 200000;
	} else if(y==3){
		ans += 100000;
	}
	if(x==1&&y==1){
		ans += 400000;
	}
	cout << ans << endl;

	return 0;
}
