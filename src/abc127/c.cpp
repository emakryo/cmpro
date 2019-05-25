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
const int Mmax = 1e5;
int N, M;
int L[Mmax], R[Mmax];

int main(){
    cin >> N >> M;
    for(int i=0; i<M; i++){
        cin >> L[i] >> R[i];
    }

    int lmax=L[0], rmin=R[0];
    for(int i=0; i<M; i++){
        lmax = max(lmax, L[i]);
        rmin = min(rmin, R[i]);
    }
    cout << rmin-lmax+1 << endl;
    return 0;
}