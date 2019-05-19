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
int N, C[10], J[10];

void solve(){
    cin >> N;
    for(int i=0; i<N; i++){
        cin >> C[i] >> J[i];
    }
    for(int x=1; x<310; x++){
        for(int y=1; y<310; y++){
            bool ok = true;
            for(int i=0; i<N; i++){
                for(int j=i+1; j<N; j++){
                    ok = (C[i]-C[j])*x < (J[j]-J[i])*y;
                    if(!ok) break;
                }
                if(!ok) break;
            }
            if(ok){
                cout << x << " " << y << endl;
                return;
            }
        }
    }
    cout << "IMPOSSIBLE" << endl;
}

int main(){
    int t;
    cin >> t;
    for(int i=0; i<t; i++){
        cout << "Case #" << i+1 << ": ";
        solve();
    }
    return 0;
}