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
#define dbg(...) debug_(__VA_ARGS__);
#else
#define dbg(...) 
#endif

int main() {
	ios_base::sync_with_stdio(false);
	int n; cin >> n;
	vector<pair<double, double>> a(n), b(n);
	for(int i=0; i<n; i++) cin >> a[i].first >> a[i].second;
	for(int i=0; i<n; i++) cin >> b[i].first >> b[i].second;

	pair<double, double> ga, gb;
	for(int i=0; i<n; i++){
		ga.first += a[i].first;
		ga.second += a[i].second;
		gb.first += b[i].first;
		gb.second += b[i].second;
	}
	ga.first /= n;
	ga.second /= n;
	gb.first /= n;
	gb.second /= n;

	for(int i=0; i<n; i++){
		a[i].first -= ga.first;
		a[i].second -= ga.second;
		b[i].first -= gb.first;
		b[i].second -= gb.second;
	}

	vector<pair<double, int>> da(n), db(n);

	for(int i=0; i<n; i++){
		da[i] = {sqrt(a[i].first*a[i].first+a[i].second*a[i].second), i};
		db[i] = {sqrt(b[i].first*b[i].first+b[i].second*b[i].second), i};
	}

	sort(da.begin(), da.end());
	sort(db.begin(), db.end());

	cout << setprecision(20) << fixed;
	cout << db[n-1].first / da[n-1].first << endl;
	return 0;
}
