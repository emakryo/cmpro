#include<bits/stdc++.h>
#include<boost/variant.hpp>
using namespace std;
typedef long long ll;
typedef vector<boost::variant<bool, ll, int, string, double>> any;
template<typename T> inline void pr(const vector<T> &xs){
	for(int i=0; i<xs.size()-1; i++) cout << xs[i] << " ";
	cout << xs[xs.size()-1] << endl;
}
template<typename T> inline void debug(const vector<T> &xs){
#ifdef DEBUG
	pr(xs);
#endif
}

int main(){
	int N;
	cin >> N;

	vector<int> items(1, 1);
	int p6=1, p9=1;
	for(int i=0; i<7; i++){
		p6 *= 6;
		p9 *= 9;
		items.push_back(p6);
		items.push_back(p9);
	}
	debug(items);

	vector<int> cnt(N+1, 1e8);
	cnt[0] = 0;
	for(int i=1; i<=N; i++){
		for(int item: items){
			if(i>=item) cnt[i] = min(cnt[i], 1+cnt[i-item]);
		}
	}

	cout << cnt[N] << endl;


	return 0;
}
