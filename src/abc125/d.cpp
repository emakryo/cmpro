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
int N;
ll A[Nmax];

int main(){
	cin >> N;
	for(int i=0; i<N; i++) cin >> A[i];

	int n_neg = 0;
	ll minA = abs(A[0]);
	ll sum = 0;
	for(int i=0; i<N; i++){
		sum += abs(A[i]);
		if(A[i] < 0) n_neg++;
		if(abs(A[i]) < minA){
			minA = abs(A[i]);
		}
	}

	if(n_neg%2){
		cout << sum-2*minA << endl;
	} else {
		cout << sum << endl;
	}

	return 0;
}
