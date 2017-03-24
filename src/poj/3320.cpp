#include<cstdio>
#include<vector>
#include<map>
#include<queue>
#include<algorithm>
#include<cmath>
#include<cassert>
using namespace std;
typedef long long ll;
const int Pmax = 1000000;
int P, X[Pmax];

int main(){
	map<int, int> count;
	scanf("%d", &P);
	for(int i=0; i<P; i++){
		scanf("%d", &X[i]);
		count[X[i]]++;
	}
	int uniq = count.size();

	int p=0,q=0,k=0;
	int ans = P;
	count = map<int, int>();
	while(q <= P){
		if(k>=uniq){
			ans = min(ans, q-p);
			count[X[p]]--;
			if(count[X[p]]==0) k--;
			p++;
		}
		else{
			count[X[q]]++;
			if(count[X[q]]==1) k++;
			q++;
		}
	}

	printf("%d\n", ans);

	return 0;
}
