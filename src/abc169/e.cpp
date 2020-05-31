#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

template<typename T>
ostream& operator<<(ostream &os, vector<T> &v){
	string sep = " ";
	if(v.size()) os << v[0];
	for(int i=1; i<v.size(); i++) os << sep << v[i];
	return os;
}

#ifdef DBG
void debug_(){ cout << endl; }
template<typename T, typename... Args>
void debug_(T&& x, Args&&... xs){
	cout << x << " "; debug_(forward<Args>(xs)...);
}
#define dbg(...) debug_(__VA_ARGS__)
#else
#define dbg(...)
#endif

int main() {
	ios_base::sync_with_stdio(false);
	cout << setprecision(20) << fixed;

	int n; cin >> n;
	vector<pair<ll, ll>> ab(n);
	vector<pair<ll, ll>> ba(n);
	for(int i=0; i<n; i++){
		cin >> ab[i].first >> ab[i].second;
		ba[i].first = ab[i].second;
		ba[i].second = ab[i].first;
	}

	sort(ab.begin(), ab.end());
	sort(ba.rbegin(), ba.rend());

	if(n%2){
		ll lb = ab[n/2].first;
		ll ub = ba[n/2].first;

		cout << ub - lb + 1 << endl;
	} else {
		ll lb1 = ab[n/2-1].first;
		ll ub1 = ba[n/2].first;

		ll lb2 = ab[n/2].first;
		ll ub2 = ba[n/2-1].first;

		dbg(lb1, ub1, lb2, ub2);

		cout << ub1+ub2 - lb1-lb2 + 1 << endl;
	}

	return 0;
}
