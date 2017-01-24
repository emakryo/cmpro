#include<iostream>
#include<iomanip>
#include<algorithm>
#include<vector>
#include<queue>
#include<map>
using namespace std;
typedef long long ll;
string S[10];

int main(){
    cin >> S[0];
    int n = S[0].size();
    for(int i=1; i<n; i++){
        S[i] = S[i-1].substr(1, n-1) + S[i-1][0];
    }

    int ans = 10;
    for(int i=1; i<(1<<n); i++){
        string r(n, 'x');
        for(int j=0; j<n; j++){
            if(!(i&(1<<j))) continue;
            for(int k=0; k<n; k++){
                r[k] = S[j][k] == 'o' ? 'o' : r[k];
            }
        }
        bool ok = true;
        for(int k=0; k<n; k++) ok = ok && r[k] == 'o';
        if(ok){
            int l=0;
            for(int j=0; j<n; j++) l += ((i&(1<<j)) > 0) ? 1 : 0;
            ans = min(ans, l);
            //cout << i << endl;
        }
    }

    cout << ans << endl;

    return 0;
}
