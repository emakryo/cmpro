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
int N, H[Nmax+1];

int main(){
	cin >> N;
	for(int i=0; i<N; i++) cin >> H[i];
	int hmax = 0;
	for(int i=0; i<N; i++) hmax = max(hmax, H[i]);

	int ans=0;
	for(int i=1; i<=hmax; i++){
		for(int j=0; j<N; j++){
			if(H[j]>=i&&H[j+1]<i) ans++;
		}
	}
	cout << ans << endl;

	return 0;
}
