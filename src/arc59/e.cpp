#include<iostream>
#include<vector>
using namespace std;
typedef long long ll;
const ll P = 1e9+7;
const int Nmax = 400;
int N, C, A[Nmax], B[Nmax];
ll s[Nmax+1][Nmax+1];
ll dp[Nmax+1][Nmax+1];

ll mpow(int a, int x, ll p){
	if(x<1) return 1;
	if(x%2) return mpow(a, x-1, p)*a%p;
	ll t = mpow(a, x/2, p);
	return t*t%p;
}

int main(){
	cin >> N >> C;
	for(int i=0; i<N; i++) cin >> A[i];
	for(int i=0; i<N; i++) cin >> B[i];

	for(int i=1; i<=400; i++){
		s[i][0] = i;
	}
	for(int j=1; j<=C; j++){
		for(int i=1; i<=400; i++){
			s[i][j] = (s[i-1][j]+mpow(i, j, P))%P;
		}
	}

	for(int j=0; j<=C; j++){
		dp[0][j] = (P+s[B[0]][j]-s[A[0]-1][j])%P;
	}
	//cout << dp[0][C] << endl;

	for(int i=1; i<N; i++){
		for(int j=0; j<=C; j++){
			for(int k=0; k<=j; k++){
				dp[i][j] += dp[i-1][j-k]*(P+s[B[i]][k]-s[A[i]-1][k]);
				dp[i][j] %= P;
				//cout << i << " " << j << " " << k << " " << s[B[i]][k]-s[A[i]-1][k] << endl;
			}
			//cout << dp[i][j] << endl;
		}
	}

	cout << dp[N-1][C] << endl;

	return 0;
}
