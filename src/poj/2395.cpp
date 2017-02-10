#include<iostream>
#include<algorithm>
#include<queue>
using namespace std;
const int Nmax = 2000;
const int Mmax = 10000;
const long INF = 1e18;
int N,M;
int A[Mmax],B[Mmax];
long L[Mmax];
vector<pair<long, int> > conn[Nmax+1];
long d[Nmax+1];

int main(){
	cin >> N >> M;
	for(int i=0; i<M; i++){
		cin >> A[i] >> B[i] >> L[i];
		conn[A[i]].push_back(make_pair(L[i], B[i]));
		conn[B[i]].push_back(make_pair(L[i], A[i]));
	}

	for(int i=1; i<=N; i++) d[i] = INF;

	priority_queue<pair<long, int>, vector<pair<long, int> >,
		greater<pair<long, int> > > que;

	que.push(make_pair(0, 1));
	d[1] = 0;

	while(!que.empty()){
		long di = que.top().first;
		int i = que.top().second;
		que.pop();

		for(int j=0; j<conn[i].size(); j++){
			long dk = conn[i][j].first;
			int k = conn[i][j].second;
			if(max(di,dk) < d[k]){
				d[k] = max(di,dk);
				que.push(make_pair(max(di,dk), k));
			}
		}
	}

	long ans=0;
	for(int i=1; i<=N; i++) ans = max(ans, d[i]);

	cout << ans << endl;
	return 0;
}
