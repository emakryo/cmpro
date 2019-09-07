#include<bits/stdc++.h>
#include<boost/variant.hpp>
using namespace std;
typedef long long ll;
typedef vector<boost::variant<bool, ll, int, string, double, char*>> any;
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
	int n2 = 1<<N;
	vector<ll> S(n2);
	for(int i=0; i<n2; i++) cin >> S[i];
	sort(S.begin(), S.end());
	reverse(S.begin(), S.end());

	vector<ll> a(1, S[0]);
	S[0] = -1;
	for(int k=0; k<N; k++){
		int j=0;
		int na = a.size();
		for(int i=na-1; i>=0; i--){
			while(j<n2&&(S[j]<0||S[j]>=a[i])) j++;
			if(j==n2){
				cout << "No" << endl;
				return 0;
			}
			a.push_back(S[j]);
			S[j++] = -1;
		}
		sort(a.begin(), a.end());
	}
	cout << "Yes" << endl;

	return 0;
}
