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
const ll P = 1e9+7;
int N;
string S1, S2;
ll x[60][9];

int main(){
	cin >> N >> S1 >> S2;

	/*
	 * 0: 0
	 * 1: 1
	 * 2: 2
	 * 3: 01
	 * 4: 02
	 * 5: 10
	 * 6: 12
	 * 7: 20
	 * 8: 21
	*/

	int i=0;
	if(S1[0] == S2[0]){
		for(int i=0; i<3; i++) x[0][i] = 1;
	}
	else{
		for(int i=3; i<9; i++) x[1][i] = 1;
		i++;
	}
	i++;


	while(i<N){
		if(S1[i] == S2[i]){
			x[i][0] = (x[i-1][1] + x[i-1][2] + x[i-1][6] + x[i-1][8])%P;
			x[i][1] = (x[i-1][2] + x[i-1][0] + x[i-1][4] + x[i-1][7])%P;
			x[i][2] = (x[i-1][0] + x[i-1][1] + x[i-1][3] + x[i-1][5])%P;
		}
		else{
			x[i+1][3] = (x[i-1][2] + x[i-1][5] + x[i-1][6] + x[i-1][7])%P;
			x[i+1][4] = (x[i-1][1] + x[i-1][5] + x[i-1][7] + x[i-1][8])%P;
			x[i+1][5] = (x[i-1][2] + x[i-1][3] + x[i-1][4] + x[i-1][8])%P;
			x[i+1][6] = (x[i-1][0] + x[i-1][3] + x[i-1][7] + x[i-1][8])%P;
			x[i+1][7] = (x[i-1][1] + x[i-1][3] + x[i-1][4] + x[i-1][6])%P;
			x[i+1][8] = (x[i-1][0] + x[i-1][4] + x[i-1][5] + x[i-1][6])%P;
			i++;
		}
		i++;
	}

	ll ans = 0;
	for(int i=0; i<9; i++) ans = (ans+x[N-1][i])%P;
	cout << ans << endl;

	return 0;
}
