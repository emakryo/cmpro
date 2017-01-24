#include<cstdio>
#include<algorithm>
#include<vector>
#include<queue>
#include<map>
#include<cmath>
using namespace std;
typedef long long ll;

int main(){
	int N[6];

	while(true){
		for(int i=0; i<6; i++) scanf("%d", &N[i]);
		bool last = true;
		for(int i=0; i<6; i++) if(N[i] != 0) last = false;
		if(last) break;

		int ans = 0;
		ans += N[5];
		
		ans += N[4];
		N[0] -= min(N[0], N[4]*11);

		ans += N[3];
		int use2 = min(N[1], N[3]*5);
		N[1] -= use2;
		N[0] -= min(N[0], N[3]*20-use2*4);

		ans += N[2]/4;
		N[2] = N[2]%4;
		if(N[2] > 0) ans += 1;
		if(N[2] == 3){
			use2 = min(N[1], 1);
		}
		else if(N[2] == 2){
			use2 = min(N[1], 3);
		}
		else if(N[2] == 1){
			use2 = min(N[1], 5);
		}
		else{
			use2 = 0;
		}
		N[1] -= use2;
		if(N[2] > 0) N[0] -= min(N[0], 36-N[2]*9-use2*4);

		ans += N[1]/9;
		N[1] = N[1]%9;
		if(N[1] > 0){
			ans += 1;
			N[0] -= min(N[0], 36-N[1]*4);
		}

		ans += N[0]/36;
		N[0] = N[0]%36;
		if(N[0] > 0) ans += 1;

		printf("%d\n", ans);
	}
	return 0;
}
