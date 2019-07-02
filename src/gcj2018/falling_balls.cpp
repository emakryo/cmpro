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
int C;
int B[100];

void solve(){
    cin >> C;
    for(int i=0; i<C; i++){
        cin >> B[i];
    }
    if(B[0]==0||B[C-1]==0){
        cout << "IMPOSSIBLE" << endl;
        return;
    }
    vector<int> to(C);
    int x=0;
    for(int i=0; i<C; i++){
        to[i]=x;
        B[x]--;
        while(B[x]==0) x++;
        // cout << to[i] << endl;
    }
    vector<string> ans;
    while(true){
        bool change = false;
        string row;
        vector<int> to_next(C, -1);
        for(int i=0; i<C; i++){
            if(to[i]==i || to[i]<0){
                row+='.';
                to_next[i] = i;
            } else if(to[i]<i){
                row+='/';
                to_next[i-1] = to[i];
                change = true;
            } else {
                row+='\\';
                to_next[i+1] = to[i];
                change = true;
            }
        }
        to = to_next;
        ans.push_back(row);
        if(!change) break;
    }

    cout << ans.size() << endl;
    for(string r: ans){
        cout << r << endl;
    }
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