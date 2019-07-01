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
const int Mmax = 2000;
int N, M;
int A[Mmax], B[Mmax];
ll C[Mmax];

int main(){
    cin >> N >> M;
    for(int i=0; i<M; i++){
        cin >> A[i] >> B[i] >> C[i];
        A[i]--; B[i]--;
    }

    vector<ll> dist(N, 1e15);
    dist[0] = 0;
    for(int i=0; i<N-1; i++){
        for(int j=0; j<M; j++){
            if(dist[A[j]] == 1e15) continue;
            if(dist[A[j]]-C[j] < dist[B[j]]){
                dist[B[j]] = dist[A[j]]-C[j];
            }
        }
    }

    vector<bool> loop(N, false);
    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++){
            if(dist[A[j]] == 1e15) continue;
            if(loop[A[j]] || dist[A[j]]-C[j] < dist[B[j]]){
                loop[B[j]] = true;
            }
        }
    }

    if(loop[N-1]) cout << "inf" << endl;
    else cout << -dist[N-1] << endl;
    return 0;
}