//#include<iostream>
//#include<iomanip>
#include<cstdio>
#include<vector>
#include<map>
#include<queue>
#include<algorithm>
#include<cmath>
using namespace std;
typedef long long ll;
const int Pmax = 40000;
int P, X[Pmax+1];

int main(){
	printf("pohe\n");
	int N;
	scanf("%d",&N);
	for(int iii=0; iii<N; iii++){
		scanf("%d", &P);
		for(int i=1; i<=P; i++){
			scanf("%d", &X[i]);
		}
		
		vector<int> dp;
		for(int i=1; i<=P; i++){
			vector<int>::iterator l = lower_bound(dp.begin(), dp.end(), X[i]);
			if(l != dp.end()){
				*l = X[i];
			}
			else{
				dp.push_back(X[i]);
			}
		}
		printf("%d\n", (int)dp.size());
	}

	return 0;
}
