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
	int n, m;
	cin >> n >> m;
	vector<vector<int>> graph(n);
	for(int i=0; i<m; i++){
		int a, b;
		cin >> a >> b;
		a--; b--;
		graph[b].push_back(a);
	}

	string s;
	cin >> s;
	int p;
	vector<int> x;
	while(s.size()>0){
		int l = s.size();
		if(s[0]=='"'){
			if(s.back()=='"'){
				x.push_back(0);
				s = s.substr(1, l-2);
			} else {
				x.push_back(1);
				s = s.substr(1, l-4);
			}
		} else {
			if(s.back() == 'w'){
				x.push_back(1);
				s = s.substr(0, l-1);
			} else {
				x.push_back(0);
			}
			s = s.substr(5, s.size()-5);
			p = atoi(s.c_str())-1;
			s = "";
		}
	}

	reverse(x.begin(), x.end());
	dbg(p);
	dbg(x);

	vector<bool> g(n);
	g[p] = true;

	for(int z: x){
		vector<int> c(n);
		int k = 0;
		for(int i=0; i<n; i++){
			if(!g[i]) continue;
			k++;
			for(int j: graph[i]){
				c[j]++;
			}
		}

		for(int i=0; i<n; i++){
			if(z){
				g[i] = c[i]>0;
			} else {
				g[i] = c[i]<k;
			}
		}
		dbg(g);
	}

	int ans = 0;
	for(int i=0; i<n; i++) {
		if(g[i]) ans++;
	}

	cout << ans << endl;

	return 0;
}
