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
const int Nmax = 2e5;
int N, A[Nmax];
ll K;

int main(){
	cin >> N >> K;
	for(int i=0; i<N; i++) cin >> A[i];

	vector<int> next(N, -1), pos(Nmax+1, -1);
	for(int i=0; i<N; i++){
		if(pos[A[i]]>=0){
			next[pos[A[i]]] = i;
		}
		pos[A[i]] = i;
	}
	for(int i=0; i<N; i++){
		if(next[pos[A[i]]]<0){
			next[pos[A[i]]] = i;
		}
	}

	int interval = 1;
	int idx = 0;
	while(idx!=N){
		if(next[idx]<=idx) interval++;
		idx = next[idx]+1;
	}

	K %= interval;

	//cout << K << endl;

	idx = 0;
	while(K>1){
		if(next[idx]<=idx) K--;
		idx = next[idx]+1;
		//cout << idx << " " << K << endl;
	}

	vector<int> ans;
	while(idx<N){
		if(next[idx]>idx) idx = next[idx]+1;
		else{
			ans.push_back(A[idx]);
			idx++;
		}
	}

	for(int i=0; i<ans.size(); i++) cout << ans[i] << (i==ans.size()-1?'\n':' ');

	return 0;
}
