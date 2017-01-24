#include<iostream>
#include<algorithm>
using namespace std;
const int Nmax = 1e6;
const int Pmax = 20;
const long long R = 1e9;
int N;
long long dp[Nmax+1];

int main(){
	cin >> N;

	dp[0] = 1;

	for(int i=1; i<=N; i++){
		if(i%2==0){
			dp[i] = (dp[i-1] + dp[i/2])%R;
		}
		else{
			dp[i] = dp[i-1];
		}
	}

	//for(int i=0; i<Pmax; i++) cout << (1<<i) << endl;
	/*
	for(int i=0; i<=N; i++){
		for(int j=0; j<Pmax; j++){
			cout << dp[i][j] << " ";
		}
		cout << endl;
	}
	*/

	cout << dp[N] << endl;
	return 0;
}
