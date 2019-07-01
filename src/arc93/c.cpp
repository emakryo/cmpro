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
int N;
const int Nmax = 1e5;
int A[Nmax];


int main(){
    cin >> N;
    for(int i=0; i<N; i++) cin >> A[i];

    vector<ll> v;
    v.push_back(0);
    for(int i=0; i<N; i++) v.push_back(A[i]);
    v.push_back(0);

    ll sum = 0;
    for(int i=0; i<v.size()-1; i++) sum += abs(v[i]-v[i+1]);

    for(int i=1; i<v.size()-1; i++){
        cout << sum - abs(v[i-1]-v[i]) - abs(v[i]-v[i+1]) + abs(v[i-1]-v[i+1]) << endl;
    }

    return 0;
}