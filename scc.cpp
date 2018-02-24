#include<iostream>
#include<vector>
#include<map>
#include<algorithm>
using namespace std;

// perform strongly connected component decomposition
class SCC{
	vector<bool> visited;
	vector<vector<int> > rev_graph;
	vector<int> visit_nodes;
	vector<int> root;
	// sort nodes by post-order of dfs
	void visit(int n){
		if(visited[n]) return;
		visited[n] = true;
		for(int i=0; i<graph[n].size(); i++){
			visit(graph[n][i]);
		}
		visit_nodes.push_back(n);
	}

	// assign component index
	void assign(int n, int r){
		if(root[n] >= 0) return;
		root[n] = r;
		for(int i=0; i<rev_graph[n].size(); i++){
			assign(rev_graph[n][i], r);
		}
	}

public:
	vector<vector<int> > graph; // original graph
	vector<vector<int> > components; // nodes lists for each components
	vector<int> component_index; // index of component to which each node belongs
	vector<vector<int> > component_graph; // graph of component index

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

		for(int i=0; i<components.size(); i++){
			sort(component_graph[i].begin(), component_graph[i].end());
			vector<int>::iterator last;
			last = unique(component_graph[i].begin(), component_graph[i].end());
			component_graph[i].resize(last - component_graph[i].begin());
		}
	}

};

int main(){
/*
 * 0 -> 1 -> 2 -> 7  8 -> 9
 * ^    |    |    ^
 * |    V    V    V
 * 3 <- 4 -> 5 -> 6
 */
	vector<vector<int> > g(10, vector<int>());
	g[0].push_back(1);
	g[1].push_back(2);
	g[1].push_back(4);
	g[2].push_back(5);
	g[2].push_back(7);
	g[3].push_back(0);
	g[4].push_back(3);
	g[4].push_back(5);
	g[5].push_back(6);
	g[6].push_back(7);
	g[7].push_back(6);
	g[8].push_back(9);
	SCC scc(g);
	for(int i=0; i<10; i++){
		cout << i << " " << scc.component_index[i] << endl;
	}
	for(int i=0; i<scc.component_graph.size(); i++){
		cout << i << ": ";
		for(int j=0; j<scc.component_graph[i].size(); j++){
			cout << scc.component_graph[i][j] << " ";
		}
		cout << endl;
	}
	return 0;
}
