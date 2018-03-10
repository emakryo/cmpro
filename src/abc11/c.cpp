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
int N, NG[3];

int main(){
	cin >> N >> NG[0] >> NG[1] >> NG[2];
	if(N == NG[0] || N == NG[1] || N == NG[2]){
		cout << "NO" << endl;
		return 0;
	}

	vector<int> dist(N+1, 1e8);
	queue<int> que;
	dist[0] = 0;
	que.push(0);
	while(!que.empty()){
		int n = que.front();
		que.pop();
		for(int i=1; i<=3; i++){
			int m = n+i;
			if(m > N) continue;
			if(dist[m] < 1e8) continue;
			if(m == NG[0] || m == NG[1] || m == NG[2]) continue;
			dist[m] = dist[n] + 1;
			que.push(m);
		}
	}

	cout << (dist[N] <= 100 ? "YES" : "NO") << endl;

	return 0;
}
