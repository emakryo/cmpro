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
int n, a[10];

int main(){
	cin >> n;
	for(int i=0; i<n; i++) cin >> a[i];

	int ans = 0;
	for(int i=0; i<n; i++){
		while(a[i]%2 == 0 || a[i]%3 == 2){
			a[i]--; ans++;
		}
	}
	cout << ans << endl;

	return 0;
}
