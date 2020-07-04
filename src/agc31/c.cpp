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

template<typename T>
istream& operator>>(istream &is, vector<T> &v){
	for(int i=0; i<v.size(); i++) is >> v[i];
	return is;
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

vector<int> ans;
void solve(int n, int p, int a, int b){
	if(n==1){
		ans.push_back(p|a);
		ans.push_back(p|b);
		return;
	}
	n--;

	int pa = a&(1<<n);
	int pb = b&(1<<n);
	int qa = a&((1<<n)-1);
	int qb = b&((1<<n)-1);

	if(pa==pb){
		solve(n, p|pa, qa, qb);
		ans.pop_back();
		int rb = ans.back();
		solve(n, p|(pa^(1<<n)), rb&((1<<n)-1), qb);
		ans.push_back(p|b);
	} else {
		solve(n, p|pa, qa, qa^1);
		solve(n, p|pb, qa^1, qb);
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cout << setprecision(20) << fixed;

	int n, a, b;
	cin >> n >> a >> b;

	int s=0;
	for(int k=0; k<n; k++){
		s+=(a>>k&1)^(b>>k&1);
	}
	if(s%2==0){
		cout << "NO" << endl;
		return 0;
	}

	solve(n, 0, a, b);

	cout << "YES" << endl;
	cout << ans << endl;
	return 0;
}
