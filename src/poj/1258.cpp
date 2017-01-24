#include<iostream>
#include<algorithm>
#include<queue>
#include<map>
using namespace std;
const int INF = 1e8;
const int Nmax = 100;
int N,D[Nmax][Nmax];
int done[Nmax];

int solve(){
	cin >> N;
	if(cin.eof()) return -1;
	for(int i=0; i<N; i++){
		for(int j=0; j<N; j++){
			cin >> D[i][j];
		}
	}
	for(int i=0; i<N; i++) done[i] = 0;

	priority_queue<pair<int, int>, vector<pair<int, int> >,
		greater<pair<int, int> > > que;
	done[0] = 1;
	for(int i=1; i<N; i++){
		que.push(make_pair(D[0][i],i));
	}

	int cost = 0;
	while(!que.empty()){
		int c=que.top().first;
		int t=que.top().second;
		que.pop();

		if(done[t]) continue;
		done[t] = 1;
		cost += c;
		for(int i=0; i<N; i++){
			if(i==t || done[i]) continue;
			que.push(make_pair(D[t][i],i));
		}
	}

	cout << cost << endl;

	return 0;
}

int main(){
	while(solve()==0) {}
	return 0;
}
