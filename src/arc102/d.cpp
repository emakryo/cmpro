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
int L;

struct edge {
	int s,t,w;
};

int main(){
	cin >> L;

	int r=0;
	while((1<<(r+1))<=L) r++;
	int k=1<<r;

	vector<edge> g;
	for(int i=0; i<r; i++){
		g.push_back({i, i+1, 0});
		g.push_back({i, i+1, 1<<i});
	}

	for(int i=r-1; i>=0; i--){
		if(k+(1<<i)-1 < L){
			g.push_back({i, r, k});
			k += (1<<i);
		}
	}

	cout << r+1 << " " << g.size() << endl;
	for(int i=0; i<g.size(); i++){
		cout << g[i].s+1 << " " << g[i].t+1 << " " << g[i].w << endl;
	}

	return 0;
}
