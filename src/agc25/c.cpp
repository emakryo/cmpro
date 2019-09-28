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
	vector<int> L(N), R(N);
	for(int i=0; i<N; i++) cin >> L[i] >> R[i];

	vector<pair<int, int>> ls(N), rs(N);
	for(int i=0; i<N; i++){
		ls[i] = {L[i], i};
		rs[i] = {R[i], i};
	}
	sort(ls.begin(), ls.end());
	reverse(ls.begin(), ls.end());
	sort(rs.begin(), rs.end());

	ll ans1 = 0;
	vector<bool> used(N);
	ll cur = 0;
	int li = 0, ri = 0;
	for(int i=0; i<N; i++){
		if(i%2){
			while(ri<N&&used[rs[ri].second]) ri++;
			if(ri==N || cur<rs[ri].first) break;
			ans1 += cur-rs[ri].first;
			used[rs[ri].second] = true;
			cur = rs[ri].first;
		} else {
			while(li<N&&used[ls[li].second]) li++;
			if(li==N||ls[li].first<cur) break;
			ans1 += ls[li].first-cur;
			used[ls[li].second] = true;
			cur = ls[li].first;
		}
	}
	ans1 += abs(cur);
	ll ans2 = 0;
	used.assign(N, false);
	cur = 0;
	li = 0;
	ri = 0;
	for(int i=0; i<N; i++){
		if(i%2==0){
			while(ri<N&&used[rs[ri].second]) ri++;
			if(ri==N || cur<rs[ri].first) break;
			ans2 += cur-rs[ri].first;
			used[rs[ri].second] = true;
			cur = rs[ri].first;
		} else {
			while(li<N&&used[ls[li].second]) li++;
			if(li==N||ls[li].first<cur) break;
			ans2 += ls[li].first-cur;
			used[ls[li].second] = true;
			cur = ls[li].first;
		}
	}

	ans2 += abs(cur);

	cout << max(ans1, ans2) << endl;

	return 0;
}
