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
const int Nmax = 2e5;
const int Kmax = 2e3;
int N, K;
ll B[2*Kmax][2*Kmax], W[2*Kmax][2*Kmax];
ll Bcum[2*Kmax+1][2*Kmax+1], Wcum[2*Kmax+1][2*Kmax+1];

int main(){
	cin >> N >> K;
	for(int i=0; i<N; i++){
		ll x, y;
		char c;
		cin >> x >> y >> c;
		if(c=='B'){
			B[x%(2*K)][y%(2*K)] += 1;
		} else {
			W[x%(2*K)][y%(2*K)] += 1;
		}
	}

	for(int x=0; x<2*K; x++){
		for(int y=0; y<2*K; y++){
			Bcum[x+1][y+1] = B[x][y] + Bcum[x][y+1] + Bcum[x+1][y] - Bcum[x][y];
			Wcum[x+1][y+1] = W[x][y] + Wcum[x][y+1] + Wcum[x+1][y] - Wcum[x][y];
		}
	}

	//for(int x=0; x<2*K; x++){
	//	for(int y=0; y<2*K; y++){
	//		cout << Bcum[x+1][y+1] << (y==2*K-1?'\n':' ');
	//	}
	//}
	//cout << endl;
	//for(int x=0; x<2*K; x++){
	//	for(int y=0; y<2*K; y++){
	//		cout << Wcum[x+1][y+1] << (y==2*K-1?'\n':' ');
	//	}
	//}

	ll ans = 0;
	for(int x=0; x<=K; x++){
		for(int y=0; y<=K; y++){
			ll b1 = Bcum[x+K][y+K]-Bcum[x+K][y]-Bcum[x][y+K]+Bcum[x][y];
			ll b2 = Bcum[x][y];
			ll b3 = Bcum[x][2*K]-Bcum[x][y+K];
			ll b4 = Bcum[2*K][y]-Bcum[x+K][y];
			ll b5 = Bcum[2*K][2*K]-Bcum[x+K][2*K]-Bcum[2*K][y+K]+Bcum[x+K][y+K];
			ll w1 = Wcum[x+K][y]-Wcum[x][y];
			ll w2 = Wcum[x][y+K]-Wcum[x][y];
			ll w3 = Wcum[2*K][y+K]-Wcum[2*K][y]-Wcum[x+K][y+K]+Wcum[x+K][y];
			ll w4 = Wcum[x+K][2*K]-Wcum[x+K][y+K]-Wcum[x][2*K]+Wcum[x][y+K];
			//cout << x << ' ' << y << ' ' << endl;
			//cout << b1 << ' ' << b2 << ' ' << b3 << ' ' << b4 << ' ' << b5 << endl;
			//cout << w1 << ' ' << w2 << ' ' << w3 << ' ' << w4 << ' ' << endl;
			ans = max(ans, b1+b2+b3+b4+b5+w1+w2+w3+w4);
		}
	}

	cout << ans << endl;

	return 0;
}
