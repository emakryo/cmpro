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
int N;
ll Xs,Ys,Xt,Yt,X[Nmax+2],Y[Nmax+2],R[Nmax+2];
double dist[Nmax+2];


int main(){
	cin >> Xs >> Ys >> Xt >> Yt;
	cin >> N;
	for(int i=1; i<N+1; i++){
		cin >> X[i] >> Y[i] >> R[i];
	}
	X[0] = Xs;
	Y[0] = Ys;
	R[0] = 0;
	X[N+1] = Xt;
	Y[N+1] = Yt;
	R[N+1] = 0;

	for(int i=0; i<N+2; i++){
		dist[i] = 1e18;
	}
	dist[0] = 0;

	priority_queue<pair<double, int>, vector<pair<double, int> >,
		greater<pair<double, int> > > que;
	que.push(make_pair(0,0));

	while(!que.empty()){
		double d = que.top().first;
		int n = que.top().second;
		que.pop();
		if(n == N+1) break;
		if(dist[n] < d) continue;
		for(int i=0; i<N+2; i++){
			if(n == i) continue;
			double dx = X[n]-X[i];
			double dy = Y[n]-Y[i];
			double di = max(0.0,sqrt(dx*dx+dy*dy)-R[n]-R[i]);
			if(d + di < dist[i]){
				dist[i] = d+di;
				que.push(make_pair(dist[i], i));
			}
		}
	}

	cout << setprecision(10) << dist[N+1] << endl;

	return 0;
}
