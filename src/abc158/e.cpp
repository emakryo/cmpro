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
	int N, P;
	cin >> N >> P;
	string S;
	cin >> S;

	if(P==2 || P==5){
		ll ans = 0;
		for(int i=0; i<N; i++){
			if((S[i]-'0')%P==0){
				ans += (i+1);
			}
		}
		cout << ans << endl;
		return 0;
	}

	vector<int> rem(N);
	int d = 1;
	for(int i=N-1; i>=0; i--){
		rem[i] = (S[i]-'0') * d % P;
		d = (10 * d) % P;
	}

	vector<int> cum(N+1);
	for(int i=1; i<=N; i++){
		cum[i] = (cum[i-1] + rem[i-1]) % P;
	}

	vector<int> cnt(10005);
	for(int i=0; i<=N; i++){
		cnt[cum[i]]++;
	}

	ll ans = 0;
	for(int i=0; i<N; i++){
		cnt[cum[i]]--;
		ans += cnt[cum[i]];
	}
	cout << ans << endl;

	return 0;
}
