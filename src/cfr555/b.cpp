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
	int n;
	string a;
	int f[9];
	cin >> n;
	cin >> a;
	for(int i=0; i<9; i++) cin >> f[i];

	string b;
	int i=0;
	while(i<n&&f[a[i]-'1']<=a[i]-'0'){
		b += a[i];
		i++;
	}
	while(i<n&&f[a[i]-'1']>=a[i]-'0'){
		b+='0'+f[a[i]-'1'];
		i++;
	}
	while(i<n){
		b+=a[i];
		i++;
	}
	cout << b << endl;

	return 0;
}
