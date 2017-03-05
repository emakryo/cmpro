#include<iostream>
#include<iomanip>
//#include<cstdio>
#include<vector>
#include<map>
#include<queue>
#include<algorithm>
#include<cmath>
using namespace std;
typedef long long ll;
const int Hmax = 1000001;

int main(){
	vector<int> factor(Hmax/4+1);
	vector<int> ans(Hmax/4+1);
	for(int i=1; 4*i+1<=Hmax; i++){
		if(factor[i] == 0){
			for(int j=1; (4*i+1)*(4*j+1)<=Hmax; j++){
				int p = (4*i+1)*(4*j+1);
				if(factor[p/4] == 0){
					factor[p/4] = i;
				}
			}
			ans[i] = ans[i-1];
		}
		else{
			if(factor[(4*i+1)/(4*factor[i]+1)/4] == 0) ans[i]=ans[i-1]+1;
			else ans[i] = ans[i-1];
		}
	}

	//for(int i=0; i<30; i++){
	//	cout << 4*i+1 << " " << factor[i] << " " << ans[i] << endl;
	//}

	while(true){
		int X;
		cin >> X;
		if(X == 0) break;
		cout << X << " " << ans[X/4] << endl;
	}


	return 0;
}
