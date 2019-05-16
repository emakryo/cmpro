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
const int Nmax = 5e5;
const ll P = 1e9+7;
int N;
int A[Nmax];

int main(){
    cin >> N;
    for(int i=0; i<N; i++) cin >> A[i];

    vector<int> cum(N+1);
    // cout << 0 << endl;
    for(int i=0; i<N; i++){
        cum[i+1] = cum[i]^A[i];
        // cout << cum[i+1] << endl;
    }
    //cout << cum[N] << endl;

    vector<int> zero_cnt(N+1);
    map<int, vector<int> > pos;
    for(int i=0; i<N; i++) {
        zero_cnt[i+1] = zero_cnt[i]+(cum[i+1]==0?1:0);
        if(cum[i+1]!=0) pos[cum[i+1]].push_back(i);
    }

    vector<vector<ll> > dp(2, vector<ll>(N+1));
    if(cum[N]!=0){
        dp[0][0] = 1;
        for(int i=0; i<N; i++){
            dp[0][i+1] = dp[0][i];
            dp[1][i+1] = dp[1][i];
            if(cum[i+1]==0){
                dp[0][i+1] += dp[1][i];
            } else if(cum[i+1]==cum[N]) {
                dp[1][i+1] += dp[0][i];
            }
            dp[0][i+1] %= P;
            dp[1][i+1] %= P;
        }
        cout << dp[0][N-1] << endl;
    } else {
        ll ans = 0;
        for(auto p: pos) {
            auto m = p.second;
            dp[0][0] = 1;
            for(int i=0; i<2*m.size(); i++){
                dp[0][i+1] = dp[0][i];
                dp[1][i+1] = dp[1][i];
                if(i%2==0){
                    dp[1][i+1] += dp[0][i];
                } else {
                    int k=0;
                    if(i<2*m.size()-1){
                        k = zero_cnt[m[i/2+1]]-zero_cnt[m[i/2]];
                        //cout << i << ":" << zero_cnt[m[(i+1)/2]] << " " << zero_cnt[m[i/2]] << endl;
                    }
                    dp[0][i+1] += k * dp[1][i];
                }
                dp[0][i+1] %= P;
                dp[1][i+1] %= P;
                // cout << dp[0][i+1] << " " << dp[1][i+1] << endl;
            }
            // cout << p.first << " " << m.size() << " " << dp[1][2*m.size()-1] << endl;
            ans += dp[1][2*m.size()-1];
            ans %= P;
        }
        ll z = 1;
        for(int i=0; i<zero_cnt[N]-1; i++) z = (2*z)%P;
        // cout << zero_cnt[N] << " " << z << endl;
        ans += z;
        cout << ans%P << endl;
    }

	return 0;
}
