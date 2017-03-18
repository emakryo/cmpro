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
ll X[Nmax], Y[Nmax];

int main(){
	cin >> N;
	for(int i=0; i<N; i++) cin >> X[i] >> Y[i];

	int ans = 0;
	for(int i=0; i<N; i++){
		for(int j=i+1; j<N; j++){
			for(int k=j+1; k<N; k++){
				ll s = (X[i]-X[k])*(Y[j]-Y[k])-(X[j]-X[k])*(Y[i]-Y[k]);
				if(s != 0 && s%2 == 0){
					ans++;
				}
			}
		}
	}
	cout << ans << endl;
	return 0;
}
