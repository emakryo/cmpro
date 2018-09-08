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
const int Nmax=2e5;
int N, A[Nmax];

int main(){
	cin >> N;
	for(int i=0; i<N; i++) cin >> A[i];

	vector<vector<int> > c(N+2, vector<int>(20));

	for(int i=1; i<=N; i++){
		for(int j=0; j<20; j++){
			c[i][j] = c[i-1][j];
			c[i][j] += (A[i-1]>>j)&1;
			//cout << c[i][j] << " ";
		}
		//cout << endl;
	}

	for(int j=0; j<20; j++){
		c[N+1][j] = 1e8;
	}

	ll ans = 0;
	for(int i=0; i<N; i++){
		int k=N-1;
		int lb=i, ub=N+1;
		while(ub-lb>1){
			int mid=(lb+ub)/2;
			bool flag=true;
			for(int j=0; j<20; j++){
				if(c[mid][j]-c[i][j]>1){
					flag=false;
				}
			}

			if(flag){
				lb=mid;
			}
			else{
				ub=mid;
			}
		}
		//cout << i << " " << lb << " " << ub << endl;
		ans += lb-i;
	}

	cout << ans << endl;

	return 0;
}
