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
int N, K, X[Nmax], Y[Nmax], C[Nmax];

int main(){
    cin >> N >> K;
    vector<vector<int> > v(2*K, vector<int>(2*K));
    for(int i=0; i<N; i++){
        ll x, y;
        char c;
        cin >> x >> y >> c;
        if(c=='B') y+=K;
        x = x%(2*K);
        y = y%(2*K);
        v[x][y] += 1;
        v[(x+K)%(2*K)][(y+K)%(2*K)] += 1;
    }
    vector<vector<int> > cum(2*K+1, vector<int>(2*K+1));
    for(int i=0; i<2*K; i++){
        for(int j=0; j<2*K; j++){
            cum[i+1][j+1] = v[i][j]+cum[i][j+1]+cum[i+1][j]-cum[i][j];
            // cout << i << " " << j << " " << v[i][j] << " " << cum[i][j] << endl;
            // cout << v[i][j] << " ";
        }
        // cout << endl;
    }

    int ans = 0;
    for(int i=0; i<=K; i++){
        for(int j=0; j<=K; j++){
            int s = cum[i+K][j+K]-cum[i][j+K]-cum[i+K][j]+cum[i][j];
            // cout << s << endl;
            ans = max(ans, s);
            ans = max(ans, N-s);
        }
    }
    cout << ans << endl;
    
    return 0;
}