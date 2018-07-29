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
typedef pair<int, int> pii;
const int INF = 1e8;
const int Nmax = 1<<20;
int N;
int P[Nmax];
pair<int, int> st[2][2*Nmax];

void init(){
	for(int i=0; i<Nmax; i++){
		st[0][Nmax+i-1] = make_pair(INF, INF);
		st[1][Nmax+i-1] = make_pair(INF, INF);
	}
	for(int i=0; i<N; i++){
		st[i%2][Nmax+i-1] = make_pair(P[i], i);
	}
	for(int i=Nmax-2; i>=0; i--){
		st[0][i] = min(st[0][2*i+1], st[0][2*i+2]);
		st[1][i] = min(st[1][2*i+1], st[1][2*i+2]);
	}
}

pair<int, int> query(bool even, int a, int b, int k, int l, int r){
	int d = even==(a%2==0)?1:0;
	if(a<=l&&r<=b){
		return st[d][k];
	}
	if(b<=l||r<=a){
		return make_pair(INF, INF);
	}
	return min(query(even, a, b, 2*k+1, l, (l+r)/2),
			query(even, a, b, 2*k+2, (l+r)/2, r));
}

int main(){
	cin >> N;
	for(int i=0; i<N; i++) cin >> P[i];

	init();

	priority_queue<pair<int, pair<int, int> >, vector<pair<int, pair<int, int> > >, greater<pair<int, pair<int, int> > > > que;
	que.push(make_pair(query(0, 0, N, 0, 0, Nmax).first, make_pair(0, Nmax)));
	vector<int> ans;
	for(int i=0; i<N/2; i++){
		pair<int, pair<int, int> > a = que.top();
		que.pop();
		pair<int, int> q1 = query(0, a.second.first, a.second.second, 0, 0, Nmax);
		pair<int, int> q2 = query(0, q1.second+1, a.second.second, 0, 0, Nmax);
		que.push(make_pair(query(0, a.second.first, q1.second, 0, 0, Nmax).first,
					make_pair(a.second.first, q1.second)));
		que.push(make_pair(query(0, q1.second+1, q2.second, 0, 0, Nmax).first,
					make_pair(q1.second+1, q2.second)));
		que.push(make_pair(query(0, q2.second+1, a.second.second, 0, 0, Nmax).first,
					make_pair(q2.second+1, a.second.second)));
		ans.push_back(q1.first);
		ans.push_back(q2.first);
	}

	for(int i=0; i<N; i++) cout << ans[i] << (i<N-1?' ':'\n');

	return 0;
}
