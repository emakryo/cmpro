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

int h, w;

int score(vector<int> &v){
	int x = 0;
	for(int i=0; i<v.size(); i++){
		int k=v[i];
		if(k==0) k+=h*w;
		x += abs(i/w-(k-1)/w) + abs(i%w-(k-1)%w);
	}
	return x;
}

int main() {
	ios_base::sync_with_stdio(false);
	cout << setprecision(20) << fixed;

	cin >> h >> w;
	vector<int> c(h*w);
	for(int i=0; i<h*w; i++) cin >> c[i];

	typedef pair<ll, vector<int>> piv;
	priority_queue<piv, vector<piv>, greater<piv>> que;
	que.push({score(c), c});
	map<vector<int>, int> dist;
	dist[c] = 0;
	while(!que.empty()){
		vector<int> c = que.top().second;
		int n = dist[c];
		que.pop();
		dbg(que.top().first);
		if(score(c) == 0){
			cout << n << endl;
			return 0;
		}
		if(n>24) continue;

		int z = -1;
		for(int i=0; i<h*w; i++) if(c[i]==0) z=i;
		vector<vector<int>> next;
		if(z>=w){
			swap(c[z], c[z-w]);
			next.push_back(c);
			swap(c[z], c[z-w]);
		}
		if(z<(h-1)*w){
			swap(c[z], c[z+w]);
			next.push_back(c);
			swap(c[z], c[z+w]);
		}
		if(z%w>0){
			swap(c[z], c[z-1]);
			next.push_back(c);
			swap(c[z], c[z-1]);
		}
		if(z%w<w-1){
			swap(c[z], c[z+1]);
			next.push_back(c);
			swap(c[z], c[z+1]);
		}

		for(auto v: next){
			if(dist.count(v)&&dist[v]<=n+1) continue;
			dist[v] = n+1;
			int s = score(v);
			que.push({(n+1)*2+s, v});
		}
	}

	return 0;
}
