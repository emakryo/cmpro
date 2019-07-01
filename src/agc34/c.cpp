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
const int Nmax = 1e5;
int N;
ll X, B[Nmax], L[Nmax], U[Nmax];

int main(){
    cin >> N >> X;
    for(int i=0; i<N; i++) cin >> B[i] >> L[i] >> U[i];

    ll behind = 0;
    for(int i=0; i<N; i++) behind += -L[i]*B[i];

    vector<pair<ll, int> > gain;
    for(int i=0; i<N; i++){
        gain.push_back({U[i]*(X-B[i])+L[i]*B[i], i});
    }
    sort(gain.begin(), gain.end());
    reverse(gain.begin(), gain.end());

    vector<ll> gain_cum(N);
    int n_top = 0;
    for(int i=0; i<N; i++){
        ll x = gain[i].first;
        int j = gain[i].second;
        gain_cum[i] = x + (i>0?gain_cum[i-1]:0);
    }
    // cout << behind << endl;
    if(behind==0){
        cout << 0 << endl;
        return 0;
    }

    ll lb=0, ub=N*X;
    while(ub-lb>1){
        ll x = (lb+ub)/2;
        ll q = x/X;
        ll r = x-q*X;
        ll sum = 0;
        for(int i=0; i<N; i++){
            int j=gain[i].second;
            ll sum_q = 0;
            if(q==0){
                sum_q += 0;
            } else if(i < q){
                sum_q += gain_cum[q] - gain[i].first;
            } else {
                sum_q += gain_cum[q-1];
            }
            ll sum_r = 0;
            if(r<=B[j]){
                sum_r += r*L[j];
            } else {
                sum_r += B[j]*L[j]+(r-B[j])*U[j];
            }
            sum = max(sum_q+sum_r, sum);
            // cout << x << " " << i << " " << q << " " << r << " " << sum_q << " " << sum_r << endl;
        }
        if(sum+behind>=0){
            ub = x;
        } else {
            lb = x;
        }
    }

    cout << ub << endl;
    return 0;
}