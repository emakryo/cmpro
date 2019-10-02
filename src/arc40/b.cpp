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
	int N, R;
	cin >> N >> R;
	string S;
	cin >> S;

	int start = 0;
	while(start<N&&S[start]=='o') start++;
	if(start==N) {
		cout << 0 << endl;
		return 0;
	}
	int end = N-1;
	while(end>=0&&S[end]=='o') end--;
	int ans = max(0, end-R+1);
	for(int i=start; i<end-R+1; i++){
		if(S[i]=='.'){
			for(int j=i; j<min(i+R, N); j++) S[j] = 'o';
			ans++;
		}
	}
	cout << ans + 1 << endl;

	return 0;
}
