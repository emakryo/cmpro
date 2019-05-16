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
    int R,G,B,N;
    cin >> R >> G >> B >> N;
    int ans = 0;
    for(int r=0; r*R<=N; r++){
        for(int g=0; g*G+r*R<=N; g++){
            if((N-g*G-r*R)%B == 0) ans ++;
        }
    }
    cout << ans << endl;
	return 0;
}
