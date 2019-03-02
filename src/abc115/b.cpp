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
const int Nmax=10;
int N, P[Nmax];

int main(){
	cin >> N;
	for(int i=0; i<N; i++) cin >> P[i];

	int imax = 0;
	for(int i=0; i<N; i++){
		if(P[i] > P[imax]) imax = i;
	}

	int ans=0;
	for(int i=0; i<N; i++){
		if(i==imax) ans += P[i]/2;
		else ans += P[i];
	}
	cout << ans << endl;

	return 0;
}
