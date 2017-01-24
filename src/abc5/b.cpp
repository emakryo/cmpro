#include<iostream>
#include<iomanip>
#include<algorithm>
#include<vector>
#include<queue>
#include<map>
#include<cmath>
using namespace std;
typedef long long ll;

int main(){
    int N, T[100];
    cin >> N;
    for(int i=0; i<N; i++) cin >> T[i];

    int ans = T[0];
    for(int i=0; i<N; i++) ans = min(ans, T[i]);
    cout << ans << endl;
	return 0;
}
