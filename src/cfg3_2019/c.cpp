#include<iostream>
#include<iomanip>
#include<cstdio>
#include<vector>
#include<map>
#include<queue>
#include<algorithm>
#include<cmath>
#include<cassert>
using namespace std;
typedef long long ll;
const int Nmax = 3e5;
int N;
int P[Nmax];

void swap(int i, int j, map<int, int> &pos){
    int tmp = P[j];
    P[j] = P[i];
    pos[P[i]] = j;
    P[i] = tmp;
    pos[tmp] = i;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin >> N;
    for(int i=0; i<N; i++) cin >> P[i];

    map<int, int> pos;
    vector<pair<int, int> > ans;
    for(int i=0; i<N; i++) pos[P[i]] = i;
    for(int i=0; i<N; i++){
        int j = i%2==0?N/2-i/2-1:N/2+i/2;
        int k = pos[j+1];
        // printf(" %d %d\n", j, k);
        if(k==j) continue;
        if(i%2==0){
            if(k>=N/2){
                swap(k, 0, pos);
                ans.push_back({k+1, 1});
                k = 0;
            }
            swap(k, N-1, pos);
            ans.push_back({k+1, N});
            k = N-1;
        } else {
            if(k<N/2){
                swap(k, N-1, pos);
                ans.push_back({k+1, N});
                k = N-1;
            }
            swap(k, 0, pos);
            ans.push_back({k+1, 1});
            k = 0;
        }
        swap(k, j, pos);
        ans.push_back({k+1, j+1});

        // for(int i=0; i<N; i++) printf("%d ", P[i]);
        // printf("\n");
    }

    printf("%d\n", ans.size());
    for(auto p: ans){
        printf("%d %d\n", p.first, p.second);
    }
    return 0;
}