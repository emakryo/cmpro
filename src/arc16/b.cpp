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
int N;
string X[100];

int main(){
	cin >> N;
	for(int i=0; i<N; i++) cin >> X[i];

	int ans = 0;
	for(int i=0; i<N; i++){
		for(int j=0; j<9; j++){
			if(X[i][j] == 'x') ans++;
			if(X[i][j] == 'o' && (i == N-1 || X[i+1][j] != 'o')) ans++;
		}
	}

	cout << ans << endl;

	return 0;
}
