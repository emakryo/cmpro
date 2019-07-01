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
int H, W, N;
int Sr, Sc;
string S, T;

int main(){
    cin >> H >> W >> N;
    cin >> Sr >> Sc;
    cin >> S >> T;

    int xmin=1, xmax=H;
    int ymin=1, ymax=W;
    for(int i=N-1; i>=0; i--){
        if(T[i]=='U') xmax = min(H, xmax+1);
        else if(T[i]=='D') xmin = max(1, xmin-1);
        if(T[i]=='L') ymax = min(W, ymax+1);
        else if(T[i]=='R') ymin = max(1, ymin-1);
        // cout << xmin << " " <<  xmax << " " << ymin << " " << ymax << endl;

        if(S[i]=='U') xmin++;
        else if(S[i]=='D') xmax--;
        if(S[i]=='L') ymin++;
        else if(S[i]=='R') ymax--;
        // cout << xmin << " " <<  xmax << " " << ymin << " " << ymax << endl;
        if(xmin>xmax || ymin>ymax){
            cout << "NO" << endl;
            return 0;
        }
    }

    if(xmin<=Sr && Sr<=xmax && ymin<=Sc && Sc<=ymax) cout << "YES" << endl;
    else cout << "NO" << endl;
    return 0;
}