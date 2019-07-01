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
int N;
const int Nmax = 1e5;
int V[Nmax];

int main(){
    cin >> N;
    for(int i=0; i<N; i++) cin >> V[i];

    map<int, int> m1, m2;
    for(int i=0; i<N; i++){
        if(i%2) m1[V[i]]++;
        else m2[V[i]]++;
    }
    vector<pair<int, int> > v1, v2;
    for(auto p: m1) v1.push_back({p.second, p.first});
    for(auto p: m2) v2.push_back({p.second, p.first});
    sort(v1.begin(), v1.end());
    sort(v2.begin(), v2.end());
    reverse(v1.begin(), v1.end());
    reverse(v2.begin(), v2.end());
    if(v1[0].second == v2[0].second){
        printf("%d\n", N-max(v1[0].first+v2[1].first, v1[1].first+v2[0].first));
    } else {
        printf("%d\n", N-v1[0].first-v2[0].first);
    }

    return 0;
}