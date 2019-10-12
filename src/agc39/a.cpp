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
	ll K;
	string S;
	cin >> S >> K;

	vector<bool> change(S.size());
	int n_change = 0;
	for(int i=0; i<S.size()-1; i++){
		if(S[i]==S[i+1]){
			change[i+1] = true;
			n_change++;
			i++;
		}
	}
	if(K==1 || S[0]!=S[S.size()-1] || change[S.size()-1]){
		cout << n_change*K << endl;
		return 0;
	}
	string T = S+S;
	vector<bool> changeT(T.size());
	int n_changeT = 0;
	for(int i=0; i<T.size()-1; i++){
		if(T[i]==T[i+1]){
			changeT[i+1] = true;
			n_changeT++;
			i++;
		}
	}
	if(changeT[T.size()-1]){
		if(K%2==0){
			cout << n_changeT*K/2 << endl;
		} else {
			cout << n_changeT*(K/2)+n_change << endl;
		}
	} else {
		cout << (n_changeT-n_change)*(K-1) + n_change << endl;
	}

	return 0;
}
