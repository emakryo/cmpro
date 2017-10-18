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
const int Nmax = 100000;
int N, K, X[Nmax];

int main(){
	cin >> N >> K;
	for(int i=0; i<N; i++){
		cin >> X[i];
	}

	priority_queue<pair<int, int> > que;
	for(int i=0; i<K; i++){
		que.push(make_pair(X[i], i+1));
	}

	for(int i=K; i<N; i++){
		int idx = que.top().second;
		int x = que.top().first;
		cout << idx << endl;
		if(X[i] < x){
			que.push(make_pair(X[i], i+1));
			que.pop();
		}
	}
	cout << que.top().second << endl;

	return 0;
}
