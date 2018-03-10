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
ll N, D, X, Y;

int main(){
	cin >> N >> D >> X >> Y;
	if(X%D != 0 || Y%D != 0 || N < (abs(X)+abs(Y))/D || (N - (abs(X)+abs(Y))/D)%2 == 1){
		cout << setprecision(10) << 0.0 << endl;
		return 0;
	}

	double ans = 0;
	for(int nx=abs(X)/D; nx<=N-abs(Y)/D; nx+=2){
		int ny = N - nx;
		int ne = (nx + X/D)/2;
		int nw = nx - ne;
		int ns = (ny + Y/D)/2;
		int nn = ny - ns;
		double a = 1;
		for(int i=0; i<ne; i++){
			a *= (double)(N-i)/(i+1)/4;
		}
		for(int i=0; i<nw; i++){
			a *= (double)(N-i-ne)/(i+1)/4;
		}
		for(int i=0; i<ns; i++){
			a *= (double)(N-i-nx)/(i+1)/4;
		}
		for(int i=0; i<nn; i++){
			a /= 4.0;
		}
		ans += a;
	}

	cout << setprecision(20) << ans << endl;

	return 0;
}
