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
	vector<int> A(N);
	for(int i=0; i<N; i++){
		cin >> A[i];
	}

	vector<int> cnt(N);
	for(int i=0; i<N; i++) cnt[A[i]]++;

	int i=1;
	while(i<N&&cnt[i]==0) i++;
	if(i==1){
		if(cnt[i]==1&&cnt[i+1]==N-1){
			cout << "Possible" << endl;
		} else if(cnt[i]==2&&N==2){
			cout << "Possible" << endl;
		} else {
			cout << "Impossible" << endl;
		}
		return 0;
	}

	if(cnt[i]>2){
		cout << "Impossible" << endl;
		return 0;
	}

	if(i==N-1 || (cnt[i]==1&&N<=2*i) || (cnt[i]==2&&N<=2*i-1)) {
		cout << "Impossible" << endl;
		return 0;
	}

	for(int j=i+1; j<=(cnt[i]==1?2*i:2*i-1); j++){
		if(cnt[j]<2) {
			cout << "Impossible" << endl;
			return 0;
		}
	}
	for(int j=(cnt[i]==1?2*i+1:2*i); i<N; i++){
		if(cnt[j]>0) {
			cout << "Impossible" << endl;
			return 0;
		}
	}

	cout << "Possible" << endl;

	return 0;
}
