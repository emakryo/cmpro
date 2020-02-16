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
	int N, M;
	cin >> N >> M;
	vector<int> P(M), S(M);
	for(int i=0; i<M; i++){
		string s;
		cin >> P[i] >> s;
		P[i]--;
		if(s=="AC"){
			S[i]=1;
		} else {
			S[i]=0;
		}
	}

	vector<int> wa(N);
	vector<bool> ac(N);
	for(int i=0; i<M; i++){
		if(S[i]==1){
			ac[P[i]]=true;
		} else {
			if(!ac[P[i]]) wa[P[i]]++;
		}
	}

	int n_ac = 0, n_pe = 0;
	for(int i=0; i<N; i++){
		if(ac[i]){
			n_ac++;
			n_pe += wa[i];
		}
	}
	cout << n_ac << " " << n_pe << endl;

	return 0;
}
