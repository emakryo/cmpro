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
int A[2][Nmax], N;

int main(){
	cin >> N;
	for(int j=0; j<2; j++){
		for(int i=0; i<N; i++){
			cin >> A[j][i];
		}
	}

	int x = A[0][0];
	for(int i=0; i<N; i++){
		x += A[1][i];
	}

	int ans = x;
	for(int i=1; i<N; i++){
		x += A[0][i] - A[1][i-1];
		ans = max(x, ans);
	}

	cout << ans << endl;

	return 0;
}
