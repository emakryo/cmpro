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
    ll X, Y;
    cin >> X >> Y;

    int k=0;
    while((1L<<k)*X<=Y) k++;
    cout << k << endl;

    return 0;
}