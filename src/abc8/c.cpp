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
int N;
ll C[Nmax];

int main(){
	cin >> N;
	for(int i=0; i<N; i++) cin >> C[i];

	vector<int> ndiv(N);
	for(int i=0; i<N; i++){
		for(int j=0; j<N ; j++){
			if(i!=j && C[j]%C[i] == 0) ndiv[j]++;
		}
	}

	double ans = 0;
	for(int i=0; i<N; i++){ // i-th coin
		double pi = 0;
		for(int j=0; j<N; j++){ // j-th position
			for(int k=0; k<=ndiv[i]; k+=2){ // k coins at left of i-th coin
				if(k>j) break;
				double a = 1;
				for(int l=0; l<ndiv[i]; l++){
					a *= (double)(j-l)/(N-1-l);
				}
				//cout << i << " " << j << " " << k << " " << a << endl;
				pi += a;
			}
		}
		ans += pi/N;
	}

	cout << setprecision(8) << ans << endl;
	return 0;
}
