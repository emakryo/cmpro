#include<iostream>
#include<iomanip>
//#include<cstdio>
#include<vector>
#include<map>
#include<queue>
#include<algorithm>
#include<cmath>
#include<cassert>
using namespace std;
typedef long long ll;
const int Nmax = 300;
const int Mmax = 1000;
int N, M, K;
char C[Nmax];
int A[Mmax], B[Mmax];

class SCC{
	vector<bool> visited;
	vector<vector<int> > rev_graph;
	vector<int> visit_nodes;
	vector<int> root;
public:
	vector<vector<int> > graph;
	vector<vector<int> > components;
	vector<int> component_index;
	vector<vector<int> > component_graph;

	SCC(vector<vector<int> > &g): graph(g){
		rev_graph = vector<vector<int> >(g.size());

		for(int i=0; i<g.size(); i++){
			for(int j=0; j<g[i].size(); j++){
				rev_graph[g[i][j]].push_back(i);
			}
		}

		visited = vector<bool>(g.size());
		visit_nodes = vector<int>();
		for(int i=0; i<g.size(); i++){
			visit(i);
		}

		root = vector<int>(g.size(), -1);
		for(int i=g.size()-1; i>=0; i--){
			int n = visit_nodes[i];
			assign(n, n);
		}

		map<int, vector<int> > root_index;
		for(int i=0; i<g.size(); i++){
			root_index[root[i]].push_back(i);
		}

		for(map<int, vector<int> >::iterator i=root_index.begin();
				i!=root_index.end(); i++){
			components.push_back(i->second);
		}

		component_index = vector<int>(g.size());
		for(int i=0; i<components.size(); i++){
			for(int j=0; j<components[i].size(); j++){
				component_index[components[i][j]] = i;
			}
		}

		component_graph = vector<vector<int> >(components.size());
		for(int i=0; i<g.size(); i++){
			for(int j=0; j<g[i].size(); j++){
				int n = component_index[i];
				int m = component_index[g[i][j]];
				if(n == m) continue;
				component_graph[n].push_back(m);
			}
		}

	}

	void visit(int n){
		if(visited[n]) return;
		visited[n] = true;
		for(int i=0; i<graph[n].size(); i++){
			visit(graph[n][i]);
		}
		visit_nodes.push_back(n);
	}

	void assign(int n, int r){
		if(root[n] >= 0) return;
		root[n] = r;
		for(int i=0; i<rev_graph[n].size(); i++){
			assign(rev_graph[n][i], r);
		}
	}

};

void topological_sort_visit(int n, vector<vector<int> > &graph, vector<int> &visited, vector<int> &order){
	if(visited[n]) return;
	visited[n] = true;
	for(int i=0; i<graph[n].size(); i++){
		topological_sort_visit(graph[n][i], graph, visited, order);
	}
	order.push_back(n);
}

void topological_sort(vector<vector<int> > &graph, vector<int> &order){
	vector<int> visited(graph.size());
	order = vector<int>(graph.size());

	for(int i=0; i<graph.size(); i++){
		topological_sort_visit(i, graph, visited, order);
	}

	reverse(order.begin(), order.end());
}

int main(){
	cin >> N >> M >> K;
	for(int i=0; i<N; i++) cin >> C[i];
	for(int i=0; i<M; i++){
		cin >> A[i] >> B[i];
		A[i]--; B[i]--;
	}

	vector<vector<int> > graph(N);
	for(int i=0; i<M; i++){
		graph[A[i]].push_back(B[i]);
	}

	SCC scc = SCC(graph);

	int n_components = scc.component_graph.size();
	vector<string> component_chars(n_components);
	for(int i=0; i<N; i++){
		component_chars[scc.component_index[i]].push_back(C[i]);
	}

	for(int i=0; i<n_components; i++){
		sort(component_chars[i].begin(), component_chars[i].end());
		//cout << i << " " << component_chars[i] << endl;
	}

	vector<int> topological_order;
	topological_sort(scc.component_graph, topological_order);
	//for(int i=0; i<n_components; i++) cout << topological_order[i] << (i==n_components-1 ? '\n' : ' ');

	vector<vector<string> > dp(n_components, vector<string>(K+1));
	for(int i=n_components-1; i>=0; i--){
		int n = topological_order[i];
		for(int j=1; j<=K; j++){
			if(j <= component_chars[n].size()) dp[n][j] = component_chars[n].substr(0, j);
			//cout << dp[n][j] << " " << n << " " << j << endl;
			for(int k=0; k<scc.component_graph[n].size(); k++){
				int m = scc.component_graph[n][k];
				for(int l=0; l<=min(j, (int)component_chars[n].size()); l++){
					string s = component_chars[n].substr(0, l) + dp[m][j-l];
					//cout << s << " " << n << " " << j << " " << m << " " << l << endl;
					if(s.size() != j) continue;
					if(dp[n][j] == "" || s < dp[n][j]){
						dp[n][j] = s;
					}
				}
			}
		}
	}

	for(int i=0; i<n_components; i++){
		for(int j=1; j<=K; j++){
			//cout << dp[i][j] << (j==K ? '\n' : ' ');
		}
	}

	string ans = dp[0][K];
	for(int i=0; i<n_components; i++){
		if(dp[i][K] == "") continue;
		if(ans == "" || dp[i][K] < ans) ans = dp[i][K];
	}

	if(ans == "") cout << -1 << endl;
	else cout << ans << endl;

	return 0;
}
