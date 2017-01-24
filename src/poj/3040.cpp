#include<cstdio>
#include<algorithm>
#include<vector>
#include<queue>
#include<map>
#include<cmath>
using namespace std;
typedef long long ll;

int main(){
	int N,C;
	int V[20],B[20];
	scanf("%d%d", &N, &C);
	map<int, int> m;
	for(int i=0; i<N; i++){
		int v,b;
		scanf("%d%d", &v, &b);
		m[v] = b;
	}
	int j=0;
	for(map<int, int>::iterator i=m.begin(); i!=m.end(); i++, j++){
		V[N-1-j] = i->first;
		B[N-1-j] = i->second;
	}

	int ans = 0;
	for(int i=0; i<N; i++){
		if(V[i] > C){
			ans += B[i];
			B[i] = 0;
		}
	}

	while(true){
		int a[20];
		int remain = C;
		for(int i=0; i<N; i++){
			a[i] = min(B[i], remain/V[i]);
			remain -= V[i]*a[i];
		}
		if(remain > 0){
			for(int i=N-1; i>=0; i--){
				if(B[i] > a[i]){
					a[i]++;
					remain -= V[i];
					break;
				}
			}
			if(remain > 0) break;
		}

		//for(int i=0; i<N; i++) printf("%d\n", a[i]);
		//printf("\n");

		int w = 1e8;
		for(int i=0; i<N; i++){
			if(a[i] <= 0) continue;
			w = min(w, B[i]/a[i]);
		}
		ans += w;
		for(int i=0; i<N; i++){
			B[i] -= a[i]*w;
		}
	}

	printf("%d\n", ans);
	return 0;

}
