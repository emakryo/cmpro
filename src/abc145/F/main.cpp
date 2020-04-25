#include<bits/stdc++.h>
using ll = long long;
using namespace std;

int main(){
    int N, K;
    cin >> N >> K;
    vector<ll> H(N+1);
    for(int i=1; i<=N; i++){
        cin >> H[i];
    }

    vector<vector<ll>> dp1(N+1, vector<ll>(N+1, 1e18));
    vector<vector<ll>> dp2(dp1);
    dp1[0][0] = 0;
    for(int i=0; i<N; i++){
        for(int j=0; j<=i; j++){
            for(int k=0; k<N; k++){
                dp2[j][k] = dp1[j][k];
                dp2[i+1][k+1] = min(dp1[j][k]+max(0ll, H[i+1]-H[j]), dp2[i+1][k+1]);
            }
        }
        dp1 = dp2;
    }

    ll ans=dp1[N][N-K];
    for(int j=0; j<=N; j++){
        for(int k=N-K; k<=N; k++){
            ans = min(ans, dp1[j][k]);
        }
    }
    cout << ans << endl;
    return 0;
}