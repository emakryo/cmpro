#include<vector>
#include<map>
using namespace std;

// perform strongly connected component decomposition
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
