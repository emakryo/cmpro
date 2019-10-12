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
	int H, W, h, w;
	cin >> H >> W >> h >> w;

	if(H%h==0&&W%w==0){
		cout << "No" << endl;
		return 0;
	}

	int x, s;
	if(H%h==0){
		x = W;
		s = w;
	} else {
		x = H;
		s = h;
	}

	vector<int> xs;
	for(int i=0; i<x; i++){
		if(i%s==0) xs.push_back((x+s-1)/s);
		else if(i%s==s-1) xs.push_back(-(x+2*s-1)/s);
		else xs.push_back(0);
	}

	cout << "Yes" << endl;
	for(int i=0; i<H; i++){
		for(int j=0; j<W; j++){
			cout << (H%h==0?xs[j]:xs[i]) << (j==W-1?'\n':' ');
		}
	} 


	return 0;
}
