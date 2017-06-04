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
int N, C[Nmax];

int main(){
	cin >> N;
	for(int i=0; i<N; i++){
		cin >> C[i];
	}

	int contMax = 1;
	int n = 0;
	for(int i=1; i<2*N; i++){
		if(C[(i-1)%N] == C[i%N]){
			n++;
			contMax = max(contMax, n);
		}
		else{
			n = 1;
		}
	}
	if(contMax >= N){
		cout << -1 << endl;
		return 0;
	}

	cout << 1+(contMax-1)/2 << endl;

	return 0;
}
