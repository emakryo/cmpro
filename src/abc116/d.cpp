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
	int N, K;
	cin >> N >> K;
	vector<pair<ll, int>> dt(N);
	for(int i=0; i<N; i++) cin >> dt[i].second >> dt[i].first;

	sort(dt.begin(), dt.end(), greater<>());

	ll sum = 0;
	ll kind = 0;
	vector<bool> used(N+1);
	vector<ll> removable;
	for(int i=0; i<K; i++){
		int t = dt[i].second;
		sum += dt[i].first;
		if(!used[t]){
			kind++;
			used[t] = true;
		} else {
			removable.push_back(dt[i].first);
		}
	}
	reverse(removable.begin(), removable.end());
	ll ans = sum + kind*kind;
	int k=0;
	for(int i=K; i<N; i++){
		if(k>=removable.size()) break;
		int t = dt[i].second;
		if(used[t]) continue;
		used[t] = true;
		sum += dt[i].first - removable[k];
		k++; kind++;
		ans = max(ans, sum+kind*kind);
	}

	cout << ans << endl;

	return 0;
}
