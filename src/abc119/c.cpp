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
const int Nmax = 8;
int N, A, B, C, L[Nmax];

int main(){
	cin >> N >> A >> B >> C;
	for(int i=0; i<N; i++) cin >> L[i];

	int ans = 1e8;
	for(int k=0; k<(1<<(2*N)); k++){
		int xa=0, xb=0, xc=0;
		int na=0, nb=0, nc=0;
		for(int i=0; i<N; i++){
			int j=(k>>(2*i))&3;
			if(j == 1){
				xa+=L[i];
				na++;
			}
			else if(j==2){
				xb+=L[i];
				nb++;
			}
			else if(j==3){
				xc+=L[i];
				nc++;
			}
		}
		if(na==0||nb==0||nc==0) continue;

		ans=min(ans, 10*(na+nb+nc-3)+abs(A-xa)+abs(B-xb)+abs(C-xc));
	}

	cout << ans << endl;



	return 0;
}
