#include<bits/stdc++.h>
#include<boost/variant.hpp>
using namespace std;
typedef long long ll;
typedef vector<boost::variant<bool, ll, int, string, double, char*, char, const char*>> any;
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
	int N, K, R, S, P;
	cin >> N >> K >> R >> S >> P;
	string T;
	cin >> T;

	ll ans = 0;
	for(int i=0; i<K; i++){
		char last = T[i];
		int count = 1;
		for(int j=1; j*K+i<N; j++){
			if(T[j*K+i]==last) count++;
			else {
				int x;
				if(last == 'r') x = P;
				else if(last == 's') x = R;
				else x = S;
				ans += (count+1)/2 * x;
				count = 1;
				last = T[j*K+i];
			}
		}
		int x;
		if(last == 'r') x = P;
		else if(last == 's') x = R;
		else x = S;
		ans += (count+1)/2 * x;
	}

	cout << ans << endl;


	return 0;
}
