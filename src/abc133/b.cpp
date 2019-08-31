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
const int Nmax = 10;
int N, D, X[Nmax][Nmax];

int main(){
	cin >> N >> D;
	for(int i=0; i<N; i++){
		for(int j=0; j<D; j++){
			cin >> X[i][j];
		}
	}

	int ans = 0;
	for(int i=0; i<N; i++){
		for(int j=i+1; j<N; j++){
			int d = 0;
			for(int k=0; k<D; k++){
				d += (X[i][k]-X[j][k])*(X[i][k]-X[j][k]);
			}

			int dsq = sqrt(d);
			for(int k=dsq-2; k<dsq+3; k++){
				if(k*k==d){
					ans++;
					break;
				}
			}
		}
	}

	cout << ans << endl;

	return 0;
}
