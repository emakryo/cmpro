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
const int Nmax = 2e5;
int INF = 1e9+7;
int n, m, ta, tb, k;
int a[Nmax], b[Nmax];

int main(){
    cin >> n >> m >> ta >> tb >> k;
    for(int i=0; i<n; i++) cin >> a[i];
    for(int i=0; i<m; i++) cin >> b[i];
    for(int i=0; i<n; i++) a[i] += ta;

    if(k >= n || k >= m){
        cout << -1 << endl;
        return 0;
    }

    int ans = 0;
    for(int ka=0; ka<=k; ka++){
        if(b[m-1]<a[ka]){
            ans = -1;
            break;
        }
        int pb = lower_bound(b, b+m, a[ka])-b;
        int jb = pb+(k-ka);
        // cout << pb << " " << jb << endl;
        if(jb >= m){
            ans = -1;
            break;
        }
        ans = max(ans, b[jb]+tb);
    }

    cout << ans << endl;
    return 0;
}