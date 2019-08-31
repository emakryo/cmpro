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
int N;
ll H, A, B, C, D, E;

int main(){
	cin >> N >> H;
	cin >> A >> B >> C >> D >> E;

	ll ans = 1e16;
	for(int x=0; x<=N; x++){
		ll y = 1+(-(B+E)*x+N*E-H)/(D+E);
		for(int d=-2; d<=2; d++){
			int yi = min((ll)(N-x), max(0ll, y+d));

		//cout << x << " " << y << " " << H+B*x+D*y-(N-x-y)*E << endl;
		//cout << x << " " << y+1 << " " << H+B*x+D*(y+1)-(N-x-y-1)*E << endl;
		//cout << x << " " << y-1 << " " << H+B*x+D*(y-1)-(N-x-y+1)*E << endl;
			if(H+B*x+D*yi-(N-x-yi)*E>0) ans = min(ans, A*x+C*yi);
		}
	}

	cout << ans << endl;

	return 0;
}
