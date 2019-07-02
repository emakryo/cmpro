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
int N, M;
ll B[Nmax], G[Nmax];

int main(){
    cin >> N >> M;
    for(int i=0; i<N; i++) cin >> B[i];
    for(int i=0; i<M; i++) cin >> G[i];
    sort(B, B+N);
    sort(G, G+M);

    if(G[0]<B[N-1]){
        cout << -1 << endl;
        return 0;
    }

    ll ans = 0;
    for(int i=0; i<N; i++) ans += B[i]*M;
    for(int i=1; i<M; i++) ans += G[i]-B[N-1];
    if(G[0]>B[N-1]){
        ans += G[0]-B[N-2];
    } else {
        ans += G[0]-B[N-1];
    }

    cout << ans << endl;
    return 0;
}