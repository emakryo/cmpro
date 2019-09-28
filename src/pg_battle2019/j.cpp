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
	string S;
	cin >> S;

	int l=1, r=N;
	vector<bool> oc(N+1);
	for(int i=0; i<(N+1)/2; i++){
		if(S[i]=='L'){
			cout << l << endl;
			oc[l]=true;
			l+=2;
		} else {
			cout << r << endl;
			oc[r]=true;
			r-=2;
		}
	}

	l = 1; r = N;
	for(int i=(N+1)/2; i<N; i++){
		if(S[i]=='L'){
			while(oc[l]) l++;
			cout << l << endl;
			oc[l]=true;
		} else {
			while(oc[r]) r--;
			cout << r << endl;
			oc[r]=true;
		}
	}

	return 0;
}
