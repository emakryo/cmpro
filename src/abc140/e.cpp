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
	vector<int> P(N);
	for(int i=0; i<N; i++) cin >> P[i];

	vector<pair<int, int>> pi(N);
	for(int i=0; i<N; i++) pi[i] = {P[i], i};
	sort(pi.begin(), pi.end());
	reverse(pi.begin(), pi.end());

	set<ll> idx;
	ll ans = 0;
	idx.insert(pi[0].second);
	for(int i=1; i<N; i++){
		int k = pi[i].second;
		auto next = idx.lower_bound(k);
		ll u1, u2, l1, l2;
		if(next == idx.end()){
			u1 = N-k;
			u2 = 0;
		} else {
			int knext = *next;
			auto nnext = ++next;
			u1 = knext-k;
			if(nnext==idx.end()){
				u2 = N-knext;
			} else {
				u2 = *nnext-knext;
			}
			--next;
		}
		if(next == idx.begin()){
			l1 = k+1;
			l2 = 0;
		} else {
			auto prev = --next;
			int kprev = *prev;
			debug(any{kprev});
			if(prev == idx.begin()){
				l1 = k - kprev;
				l2 = kprev+1;
			} else {
				auto pprev = --prev;
				l1 = k - kprev;
				l2 = kprev - *pprev;
			}
		}
		idx.insert(k);
		debug(any{k, l2, l1, u1, u2});
		ans += pi[i].first * (u2*l1 + u1*l2);
	}

	cout << ans << endl;

	return 0;
}
