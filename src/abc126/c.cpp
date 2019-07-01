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
    int N, K;
    cin >> N >> K;
    double ans = 0;
    for(int i=1; i<=N; i++){
        if(i>=K) ans += 1.0/N;
        else{
            int k = ceil(log2((double)K/i));
            // cout << i << " " << k << endl;
            ans += 1.0/N/(1<<k);
        }
    }
    cout << setprecision(20) << ans << endl;
    return 0;
}