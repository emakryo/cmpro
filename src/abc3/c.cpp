#include<iostream>
#include<iomanip>
#include<algorithm>
#include<vector>
#include<queue>
#include<map>
#include<cmath>
using namespace std;
typedef long long ll;
const int Nmax = 100;
int N, K, R[Nmax];

int main(){
	cin >> N >> K;
	for(int i=0; i<N; i++) cin >> R[i];

	sort(R, R+N);

	double ans = 0;
	for(int i=N-K; i<N; i++){
		ans = (ans + R[i])*0.5;
	}

	cout << setprecision(15) << ans << endl;

	return 0;
}
