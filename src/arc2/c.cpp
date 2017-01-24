#include<iostream>
#include<iomanip>
#include<algorithm>
#include<vector>
#include<queue>
#include<map>
#include<cmath>
using namespace std;
typedef long long ll;
const char com[] = {'A', 'B', 'X', 'Y'};
const int Nmax = 1000;
int N;
string S;
int dp[Nmax];

int main(){
	cin >> N >> S;

	int ans = N;
	for(int l0=0; l0<4; l0++){
		for(int l1=0; l1<4; l1++){
			for(int r0=0; r0<4; r0++){
				for(int r1=0; r1<4; r1++){
					if(l0 == r0 && l1 == r1){
						continue;
					}
					dp[0] = 1;
					if((S[0] == com[r0] && S[1] == com[r1]) ||
							(S[0] == com[l0] && S[1] == com[l1])){
						dp[1] = 1;
					}
					else{
						dp[1] = 2;
					}

					for(int i=2; i<N; i++){
						if((S[i-1] == com[r0] && S[i] == com[r1]) ||
							(S[i-1] == com[l0] && S[i] == com[l1])){
							dp[i] = min(dp[i-1]+1, dp[i-2]+1);
						}
						else{
							dp[i] = min(dp[i-1]+1, dp[i-2]+2);
						}
					}
					/*
					cout << com[l0] << com[l1] << " ";
					cout << com[r0] << com[r1] << " " << dp[N-1] << endl;
					*/
					ans = min(ans, dp[N-1]);
				}
			}
		}
	}

	cout << ans << endl;

	return 0;
}
