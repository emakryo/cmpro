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
    int N, A, B, C, D;
    string S;
    cin >> N >> A >> B >> C >> D;
    cin >> S;
    A--;
    B--;
    C--;
    D--;
    bool ans = true;
    for(int i=A; i<max(C, D)-1; i++){
        if(S[i]=='#'&&S[i+1]=='#') ans = false;
    }
    // cout << (ans?"Yes":"No") << endl;
    if(C > D){
        bool tmp = false;
        for(int i=B-1; i<D; i++){
            if(S.substr(i, 3) == "...") tmp = true;
        }
        ans = ans && tmp;
    }
    cout << (ans?"Yes":"No") << endl;
    return 0;
}