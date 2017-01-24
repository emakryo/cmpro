#include<iostream>
#include<iomanip>
#include<algorithm>
#include<vector>
#include<queue>
#include<map>
#include<cmath>
using namespace std;
typedef long long ll;
const int Nmax = 1000;
int N, X[Nmax], Y[Nmax], T[Nmax], R[Nmax];
double graph[Nmax][Nmax];

int main(){
	cin >> N;
	for(int i=0; i<N; i++){
		cin >> X[i] >> Y[i] >> T[i] >> R[i];
	}
	for(int i=0; i<N; i++){
		for(int j=0; j<N; j++){
			double d = sqrt((X[i]-X[j])*(X[i]-X[j])+(Y[i]-Y[j])*(Y[i]-Y[j]));
			graph[i][j] = max(d/T[i], d/R[j]);
			//cout << graph[i][j] << " ";
		}
		//cout << endl;
	}

	vector<double> dist(N, 1e10);
	priority_queue<pair<double, int>, vector<pair<double, int> >,
		greater<pair<double, int> > > que;
	dist[0] = 0;
	que.push(make_pair(0, 0));
	while(!que.empty()){
		double d = que.top().first;
		int n = que.top().second;
		que.pop();
		if(dist[n] < d) continue;
		for(int i=0; i<N; i++){
			double nd = d+graph[n][i];
			if(nd > dist[i] || i == n) continue;
			que.push(make_pair(nd, i));
			dist[i] = nd;
		}
	}

	/*
	for(int i=0; i<N; i++) cout << dist[i] << " ";
	cout << endl;
	*/

	double ans = 0;

	sort(dist.begin(), dist.end());
	for(int i=1; i<N; i++){
		ans = max(ans, dist[i]+(N-i-1));
	}

	cout << setprecision(10) << ans << endl;

	return 0;
}
