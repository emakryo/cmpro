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
const int Nmax = 100;
int N;
ll X, A[Nmax];

int main(){
	cin >> N >> X;
	for(int i=0; i<N; i++) cin >> A[i];

	ll sum = 0;
	for(int i=0; i<N; i++) sum += A[i];
	if(sum == X){
		cout << N << endl;
		return 0;
	}
	if(sum <= X){
		cout << N-1 << endl;
		return 0;
	}

	sort(A, A+N);

	sum = 0;
	for(int i=0; i<N; i++){
		sum += A[i];
		if(sum > X){
			cout << i << endl;
			return 0;
		}
	}

	return 0;
}
