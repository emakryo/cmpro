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
int N, X[Nmax], Y[Nmax];
ll H[Nmax];

int main(){
	cin >> N;
	for(int i=0; i<N; i++) cin >> X[i] >> Y[i] >> H[i];

	for(int x=0; x<=100; x++){
		for(int y=0; y<=100; y++){
			ll h = 1e9;
			for(int i=0; i<N; i++){
				if(H[i]==0) continue;
				if(h==1e9){
					h = abs(x-X[i])+abs(y-Y[i])+H[i];
				} else if(h != abs(x-X[i])+abs(y-Y[i])+H[i]){
					h = -1;
					break;
				}
			}
			for(int i=0; i<N; i++){
				if(H[i]>0) continue;
				if(h-abs(x-X[i])-abs(y-Y[i])>0){
					h = -1;
					break;
				}
			}
			if(h>0){
				cout << x << " " << y << " " << h << endl;
				return 0;
			}
		}
	}

	return 0;
}
