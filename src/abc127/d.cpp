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
const int Nmax=1e5, Mmax=1e5;
int N, M, B[Nmax];
ll A[Nmax], C[Mmax];

int main(){
    ll bsum = 0;
    cin >> N >> M;
    for(int i=0; i<N; i++) cin >> A[i];
    for(int i=0; i<M; i++){
        cin >> B[i] >> C[i];
    }

    sort(A, A+N);
    reverse(A, A+N);

    vector<pair<ll, int> > ops;
    for(int i=0; i<M; i++) ops.push_back({C[i], B[i]});
    sort(ops.begin(), ops.end());
    reverse(ops.begin(), ops.end());

    int j=0,k=0;
    ll ans = 0;
    for(int i=0; i<N; i++){
        if(k==M || A[j]>=ops[k].first){
            ans += A[j];
            j++;
        } else {
            ans += ops[k].first;
            if(ops[k].second==1) k++;
            else ops[k].second--;
        }
    }

    cout << ans << endl;
    return 0;
}