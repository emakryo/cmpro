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
    ll N, K;
    cin >> N >> K;
    if(N==1){
        if(K==0){
            cout << "0 0 1 1" << endl;
        } else {
            cout << -1 << endl;
        }
        return 0;
    }
    if(N==0){
        if(K==0){
            cout << "0 0" << endl;
        } else {
            cout << -1 << endl;
        }
        return 0;
    }
    if(K>=(1<<N)){
        cout << -1 << endl;
        return 0;
    }
    for(int i=0; i<(1<<N); i++){
        if(i==K) continue;
        cout << i << " ";
    }
    cout << K << " ";
    for(int i=(1<<N)-1; i>=0; i--){
        if(i==K) continue;
        cout << i << " ";
    }
    cout << K << endl;
    return 0;
}