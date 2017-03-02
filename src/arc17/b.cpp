#include<iostream>
#include<iomanip>
//#include<cstdio>
#include<vector>
#include<map>
#include<queue>
#include<algorithm>
#include<cmath>
using namespace std;
typedef long long ll;
const int Nmax = 300000;
int N, K;
int A[Nmax];

int main(){
	cin >> N >> K;
	for(int i=0; i<N; i++) cin >> A[i];

	int ans = 0;
	int start = 0;
	for(int i=1; i<K; i++){
		if(A[i] <= A[i-1]) start = i;
	}
	for(int i=0; i<=N-K; i++){
		if(start <= i){
			ans++;
			//cout << i << endl;
		}
		if(i+K < N && A[i+K] <= A[i+K-1]){
			start = i+K;
		}
	}

	cout << ans << endl;

	return 0;
}
