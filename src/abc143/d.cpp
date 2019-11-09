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
	int N;
	cin >> N;
	vector<int> L(N);
	for(int i=0; i<N; i++) cin >> L[i];

	sort(L.begin(), L.end());

	ll ans = 0;
	for(int i=0; i<N; i++){
		for(int j=i+1; j<N; j++){
			ans += lower_bound(L.begin()+j+1, L.end(), L[i]+L[j])
				- (L.begin()+j+1);
		}
	}

//	ll t = 0;
//	for(int i=0; i<N; i++) for(int j=i+1; j<N; j++) for(int k=j+1; k<N; k++){
//		if(L[i]<L[j]+L[k]&&L[j]<L[i]+L[k]&&L[k]<L[i]+L[j]) t++;
//	}

	cout << ans << endl;

	return 0;
}
