//#include<iostream>
//#include<iomanip>
#include<cstdio>
#include<vector>
#include<map>
#include<queue>
#include<algorithm>
#include<cmath>
#include<cassert>
using namespace std;
typedef long long ll;
const int Nmax = 5000;
int N;
bool D[Nmax];

int main(){
	scanf("%d", &N);
	for(int i=0; i<N; i++){
		char c[10];
		scanf("%s", c);
		D[i] = c[0] == 'F';
	}

	int Kans = 1, Mans = N;
	for(int k=1; k<=N; k++){
		int nflip = 0;
		int kflip = nflip;
		vector<bool> flip(N);
		for(int i=0; i<N-k+1; i++){
			if(kflip%2==0){
				flip[i] = !D[i];
			}
			else{
				flip[i] = D[i];
			}
			if(flip[i]) nflip++;
			if(i-k+1>=0){
				kflip += flip[i] - flip[i-k+1];
			}
			else{
				kflip += flip[i];
			}
		}
		//for(int i=0; i<N-k+1; i++) printf("%d ", (int)flip[i]);
		//puts("");
		bool ok = true;
		for(int i=N-k+1; i<N; i++){
			ok = ok && ((kflip%2==0) == D[i]);
			if(i-k+1>=0) kflip -= flip[i-k+1];
		}
		if(ok && nflip < Mans){
			Mans = nflip;
			Kans = k;
		}
	}

	printf("%d %d\n", Kans, Mans);

	return 0;
}
