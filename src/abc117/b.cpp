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
int N, L[100];

int main(){
	cin >> N;
	for(int i=0; i<N; i++) cin >> L[i];

	int k, lmax=0;
	for(int i=0; i<N; i++){
		if(L[i]>lmax){
			lmax = L[i];
			k = i;
		}
	}
	int lsum=0;
	for(int i=0; i<N; i++){
		if(i==k) continue;
		lsum += L[i];
	}

	cout << (lsum > lmax?"Yes":"No") << endl;

	return 0;
}
