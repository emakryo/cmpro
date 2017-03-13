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
const int Nmax = 1000000;
int N;
ll A[Nmax];

int main(){
	cin >> N;
	for(int i=0; i<N; i++) cin >> A[i];
	sort(A,A+N);

	int possible = 0;
	ll sum = A[0];
	for(int i=1; i<N; i++){
		if(2*sum < A[i]){
			possible = i;
		}
		sum += A[i];
	}
	cout << N-possible << endl;

	return 0;
}
