#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int Nmax = 2e5;
int N;
ll X[Nmax], Y[Nmax];

int main(){
	cin >> N;
	for(int i=0; i<N; i++) cin >> X[i] >> Y[i];

	ll amax = 0, amin = 1e10;
	for(int i=0; i<N; i++){
		amax = max(amax, max(X[i], Y[i]));
		amin = min(amin, min(X[i], Y[i]));
	}

	ll min_max = max(X[0], Y[0]);
	ll max_min = min(X[0], Y[0]);
	for(int i=1; i<N; i++){
		min_max = min(min_max, max(X[i], Y[i]));
		max_min = max(max_min, min(X[i], Y[i]));
	}
	ll ans = (amax-min_max)*(max_min-amin);

	vector<pair<ll, int>> mins;
	for(int i=0; i<N; i++) mins.push_back({min(X[i], Y[i]), i});
	sort(mins.begin(), mins.end());
	ll min_min = mins[0].first;
	max_min = mins[N-1].first;
	min_max = 1e10;
	ll max_max = 0;
	ll min_diff = min_max-min_min;
	for(int i=0; i<N; i++) {
		int k = mins[i].second;
		ll m = max(X[k], Y[k]);
		if(mins[i].first > min_max) break;
		min_max = min(min_max, m);
		max_max = max(max_max, m);
		min_min = i==N-1?1e10:mins[i+1].first;
		//cout << max_max << " " << max_min << " " << min_max << " " << min_min << endl;
		min_diff = min(min_diff, max(max_max, max_min)-min(min_max, min_min));
	}
	ans = min((amax-amin)*min_diff, ans);

	cout <<  ans << endl;

	return 0;
}
