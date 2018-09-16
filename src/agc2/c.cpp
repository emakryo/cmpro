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
const int Nmax=1e5;
int N;
ll L, A[Nmax];

int main(){
	cin >> N >> L;
	for(int i=0; i<N; i++) cin >> A[i];

	int n = -1;
	for(int i=0; i<N-1; i++){
		if(A[i]+A[i+1]>=L){
			n = i;
			break;
		}
	}

	if(n < 0){
		cout << "Impossible" << endl;
		return 0;
	}

	cout << "Possible" << endl;
	for(int i=0; i<n; i++){
		cout << i+1 << endl;
	}
	for(int i=N-2; i>=n; i--){
		cout << i+1 << endl;
	}

	return 0;
}
