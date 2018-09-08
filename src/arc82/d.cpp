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
int N, A[Nmax];

int main(){
	cin >> N;
	for(int i=0; i<N; i++){
		cin >> A[i];
		A[i]--;
	}

	int ans = 0;
	for(int i=0; i<N-1; i++){
		if(A[i]==i){
			ans++;
			swap(A[i], A[i+1]);
		}
	}
	if(A[N-1]==N-1){
		ans++;
		swap(A[N-2], A[N-1]);
	}

	//for(int i=0; i<N; i++){
	//	cout << A[i] << (i==N-1?'\n':' ');
	//}

	cout << ans << endl;

	return 0;
}
