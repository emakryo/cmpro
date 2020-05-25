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

	int n, m;
	cin >> n >> m;
	vector<vector<int>> graph(n);
	for(int i=0; i<m; i++){
		int a, b;
		cin >> a >> b;
		a--; b--;
		graph[a].push_back(b);
		graph[b].push_back(a);
	}

	map<int, int> deg;
	for(int i=0; i<n; i++){
		int d = graph[i].size();
		if(d%2){
			cout << "No" << endl;
			return 0;
		}
		deg[d]++;
	}

	dbg(deg[2], deg[4], deg[6]);

	if(deg[2]==n||deg[2]==n-1&&deg[4]==1){
		cout << "No" << endl;
		return 0;
	}
	if(deg[2]+deg[4]<n||deg[4]>2) {
		cout << "Yes" << endl;
		return 0;
	}

	int x=-1, y=-1;
	for(int i=0; i<n; i++){
		if(graph[i].size()==4){
			if(x<0) x=i;
			else y=i;
		}
	}

	vector<bool> visit(n);
	queue<int> que;
	que.push(x);
	int n_path = 0;
	while(!que.empty()){
		int v = que.front();
		que.pop();
		if(visit[v]) continue;
		visit[v] = true;
		for(int u:graph[v]){
			if(u==y){
				n_path++;
			} else if(u!=x&&!visit[u]){
				que.push(u);
			}
		}
	}

	if(n_path==2){
		cout << "Yes" << endl;
	} else {
		cout << "No" << endl;
	}
	return 0;
}
