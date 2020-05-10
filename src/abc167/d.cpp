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
	ll k; cin >> k;
	vector<int> a(n);
	for(int i=0; i<n; i++){
		cin >> a[i];
		a[i]--;
	}

	vector<int> visit(n, -1);
	vector<int> xs;
	int x = 0;
	int i = 0;
	while(visit[x]<0){
		visit[x]=i++;
		xs.push_back(x);
		x = a[x];
	}
	int l = i-visit[x];
	int b = visit[x];
	int ans;
	if(k<i){
		ans = xs[k];
	} else {
		ans = xs[(k-b)%l+b];
	}


	cout << ans+1 << endl;
	return 0;
}
