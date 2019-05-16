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
    int N;
    int ba=0, xa=0, bx=0;
    int ans = 0;
    cin >> N;
    for(int i=0; i<N; i++){
        string s;
        cin >> s;
        if(s[0] == 'B' && s[s.size()-1] == 'A') ba++;
        else if(s[0] == 'B') bx++;
        else if(s[s.size()-1] == 'A') xa++;
        for(int i=0; i<s.size()-1; i++){
            if(s[i]=='A'&&s[i+1]=='B') ans++;
        }
    }

    if(ba > 0) {
        ans += ba-1;
        if(xa>0){
            ans += 1;
            xa--;
        }
        if(bx>0){
            ans += 1;
            bx--;
        }
    }
    ans += min(xa, bx);

    cout <<  ans << endl;

	return 0;
}
