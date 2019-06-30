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
int N, X, L[Nmax];

int main(){
	cin >> N >> X;
	for(int i=0; i<N; i++) cin >> L[i];

	vector<int> cum(N);
	cum[0] = L[0];
	for(int i=1; i<N; i++) cum[i] = cum[i-1]+L[i];

	int ans = 1;
	for(int i=0; i<N; i++){
		if(cum[i] <= X) ans++;
	}
	cout << ans << endl;

	return 0;
}
