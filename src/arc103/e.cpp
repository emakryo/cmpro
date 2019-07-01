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
const int Nmax = 1e5;
string S;

int main(){
    cin >> S;

    int N = S.size();
    if(S[0]=='0'||S[N-2]=='0'||S[N-1]=='1'){
        printf("-1\n");
        return 0;
    }
    for(int i=1; i<N/2; i++){
        if(S[i]!=S[N-i-2]){
            printf("-1\n");
            return 0;
        }
    }

    queue<int> que;
    que.push(1);
    for(int i=1; i<N/2; i++){
        if(S[i]=='1'){
            while(!que.empty()){
                printf("%d %d\n", que.front(), i+1);
                que.pop();
            }
        }
        que.push(i+1);
    }
    for(int i=N/2; i<N-1; i++){
        que.push(i+1);
    }
    while(!que.empty()){
        printf("%d %d\n", que.front(), N);
        que.pop();
    }
    return 0;
}