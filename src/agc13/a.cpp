#include<bits/stdc++.h>
#include<boost/variant.hpp>
using namespace std;
typedef long long ll;
typedef vector<boost::variant<bool, ll, int, string, double, char*, const char*>> any;
template<typename T> inline void pr(const vector<T> &xs){
	for(int i=0; i<xs.size()-1; i++) cout<<xs[i]<<" ";
	(xs.empty()?cout:(cout<<xs[xs.size()-1]))<<endl;
}
template<typename T> inline void debug(const vector<T> &xs){
#ifdef DEBUG
	pr(xs);
#endif
}

int main(){
	int N;
	cin >> N;
	vector<ll> A(N);
	for(int i=0; i<N; i++) cin >> A[i];

	int s = 0;
	int ans = 1;
	for(int i=1; i<N; i++){
		if(A[i-1] < A[i]){
			if(s > 0) {
			} else if(s < 0){
				ans++;
				s = 0;
			} else {
				s = 1;
			}
		} else if(A[i] < A[i-1]){
			if(s > 0){
				ans++;
				s = 0;
			} else if(s < 0) {
			} else {
				s = -1;
			}
		}
	}

	cout << ans << endl;


	return 0;
}
