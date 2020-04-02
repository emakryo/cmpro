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
	int N, X, Y;
	cin >> N >> X >> Y;

	vector<int> ans(N);

	X--; Y--;
	for(int i=0; i<N; i++){
		for(int j=i+1; j<N; j++){
			int d = j-i;
			d = min(d, 1+abs(X-i)+abs(Y-j));
			d = min(d, 1+abs(X-j)+abs(Y-i));
			ans[d]++;
			debug(i, j, d);
		}
	}

	for(int k=1; k<N; k++) cout << ans[k] << endl;

	return 0;
}
