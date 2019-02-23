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

	ll ans = 1e10;
	for(int i=0; i<N; i++) ans = min(ans, A[i]);
	bool change = true;
	while(change){
		change = false;
		for(int i=0; i<N; i++){
			if(A[i] > ans) A[i] = A[i] % ans;
		}
		for(int i=0; i<N; i++){
			if(A[i]>0 && A[i]<ans){
				ans = A[i];
				change = true;
			}
		}
	}

	cout << ans << endl;
	return 0;
}
