#include<iostream>
#include<iomanip>
//#include<cstdio>
#include<vector>
#include<map>
#include<set>
#include<queue>
#include<algorithm>
#include<cmath>
#include<cassert>
using namespace std;
typedef long long ll;
int N;
const int Nmax = 300;
ll C[Nmax], J[Nmax];

ll gcd(ll x, ll y){
    if(y==0) return x;
    else return gcd(y, x%y);
}

void solve(){
    cin >> N;
    for(int i=0; i<N; i++){
        cin >> C[i] >> J[i];
    }

    set<pair<int, int> > rs;
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            if((C[i]-C[j])*(J[i]-J[j])>=0) continue;
            ll g = gcd(abs(C[i]-C[j]), abs(J[i]-J[j]));
            rs.insert({abs(C[i]-C[j])/g, abs(J[i]-J[j])/g});
        }
    }
    cout << rs.size()+1 << endl;
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