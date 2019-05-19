#include<iostream>
#include<iomanip>
//#include<cstdio>
#include<vector>
#include<map>
#include<queue>
#include<algorithm>
#include<cmath>
#include<cassert>
#include<random>
using namespace std;
typedef long long ll;

int solve(){
    int n;
    int start = 75;
    int target = 10;
    vector<pair<double, int> > ns(20, {10000, 0});
    for(int i=0; i<99; i++){
        cin >> n;
        if(n<0) return -1;
        // cerr << n << endl;
        if(i<target-1){
            cout << i+2 << " 100" << endl;
        } else if(i<start){
            cout << target+i%(20-target)+1 << " " << i << endl;
        } else if(i<start+target){
            cout << n-start << " 0" << endl;
            int k;
            cin >> k;
            ns[n-start-1] = {k+1.0/20*(start-n-1), n-start-1};
            for(int j=0; j<k; j++){
                int x;
                cin >> x;
            }
            // cerr << n-start-1 << " " << ns[n-start-1].first << endl;
        } else {
            if(n==start+target){
                ns[0].first += 1;
            }
            sort(ns.begin(), ns.end());
            cout << ns[1].second+1 << " " << i+1 << endl;
            ns[1].first += 1;
        }
    }
    cin >> n;
    cout << 1 << " " << 100 << endl;
    return 0;
}

int main(){
    int t;
    cin >> t;
    for(int i=0; i<t; i++){
        if(solve()<0) break;
    }
    return 0;
}