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
const int Nmax = 1e5;
int N, M, X[Nmax], Y[Nmax];

int main(){
	cin >> N >> M;
	for(int i=0; i<M; i++){
		cin >> X[i] >> Y[i];
		X[i]--; Y[i]--;
	}

	vector<int> ur(N), uw(N), lr(N), lw(N), t(N);
	ur[0]=lr[0]=t[0]=1;
	for(int i=1; i<N; i++) uw[i]=lw[i]=t[i]=1;

	for(int i=0; i<M; i++){
		t[X[i]]--;
		t[Y[i]]++;
		if(uw[X[i]]==0){
			ur[X[i]]--;
			lr[X[i]]--;
			ur[Y[i]]++;
			lr[Y[i]]++;
		} else if(ur[X[i]]==0){
			uw[X[i]]--;
			lw[X[i]]--;
			uw[Y[i]]++;
			lw[Y[i]]++;
		} else {
			lr[X[i]] = max(0, lr[X[i]]-1);
			lw[X[i]] = max(0, lw[X[i]]-1);
			ur[Y[i]]++;
			uw[Y[i]]++;
		}
		if(t[X[i]]==0){
			lr[X[i]]=ur[X[i]]=lw[X[i]]=uw[X[i]]=0;
		}
	}

	int ans = 0;
	for(int i=0; i<N; i++){
		if(t[i]>0 && ur[i]>0) ans++;
	}
	cout << ans << endl;

	return 0;
}
