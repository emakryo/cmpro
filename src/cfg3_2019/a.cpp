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
    ll a, b, c;
    cin >> a >> b >> c;
    ll ans = 2*min(a, b) + 2*c;
    if(a-min(a, b)>0) ans++;
    if(b-min(a, b)>0) ans++;
    cout << ans << endl;
    return 0;
}