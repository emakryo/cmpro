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
	int n, q;
	cin >> n >> q;
	vector<vector<bool>> follow(n, vector<bool>(n));

	for(int i=0; i<q; i++){
		int c;
		cin >> c;
		vector<pair<int, int>> f;
		if(c==1){
			int a, b;
			cin >> a >> b;
			a--; b--;
			f.emplace_back(a,b);
		} else if(c==2){
			int a;
			cin >> a;
			a--;
			for(int j=0; j<n; j++){
				if(j==a) continue;
				if(follow[j][a]) f.emplace_back(a, j);
			}
		} else {
			int a;
			cin >> a;
			a--;
			for(int j=0; j<n; j++){
				if(!follow[a][j]) continue;
				for(int k=0; k<n; k++){
					if(k==j) continue;
					dbg(a, j, k, follow[a][j], follow[j][k])
					if(follow[j][k] && a!=k) f.emplace_back(a, k);
				}
			}
		}
		for(auto p: f){
			follow[p.first][p.second]=true;
		}
	}

	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			cout << (follow[i][j]?"Y":"N");
		}
		cout << endl;
	}

	return 0;
}
