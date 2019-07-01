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

int main(){
	int A, B, C, D, E, F;
	cin >> A >> B >> C >> D >> E >> F;

	int ans_x=100*A, ans_y=0;
	for(int na=0; na<=30; na++){
		if(100*A*na > F) continue;
		for(int nb=0; nb<=30; nb++){
			if(100*(A*na+B*nb) > F) continue;
			for(int nc=0; C*nc<=(A*na+B*nb)*E; nc++){
				if(100*(A*na+B*nb)+C*nc > F) continue;
				for(int nd=0; D*nd<=(A*na+B*nb)*E-C*nc; nd++){
					int x = 100*(A*na+B*nb);
					int y = C*nc+D*nd;
					if(x+y > F) continue;
					if(y > x*E/100) continue;
					//cout << na << " " << nb << " " << nc << " " << nd << endl;
					if((double)ans_y/ans_x < (double)y/(x+y)){
						ans_x = x+y;
						ans_y = y;
					}
				}
			}
		}
	}

	cout << ans_x << " " << ans_y << endl;

	return 0;
}
