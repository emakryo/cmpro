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
string S;
int main(){
    cin >> S;
    int i=0;
    ll ans = 0;
    ll na = 0;
    while(S.size() > 2 && i<S.size()-2){
        if(S.substr(i, 3) == "ABC"){
            S.replace(i, 3, "BCA");
            ans += na+1;
            i+=2;
        } else if(S[i]=='A'){
            na++;
            i++;
        } else {
            na = 0;
            i++;
        }
        // cout << i << " " << ans << " " << S << endl;
    }
    cout << ans << endl;
    return 0;
}