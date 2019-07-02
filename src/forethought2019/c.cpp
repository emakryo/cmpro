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

int solve(){
	int n;
	cin >> n;

	int x = 0;
	for(int i=0; i<9; i++){
		vector<int> a, b;
		for(int j=1; j<=n; j++){
			if(j&(1<<i)) a.push_back(j);
			else b.push_back(j);
		}
		if(a.size()==0||b.size()==0) break;
		cout << a.size() << " ";
		cout << b.size() << " ";
		for(int j=0; j<a.size(); j++) cout << a[j] << " ";
		for(int j=0; j<b.size(); j++) cout << b[j] << (j==b.size()-1?'\n':' ');
		cout.flush();

		int r;
		cin >> r;
		if(r<0) return -1;
		x = max(x, r);
	}

	cout << "-1 " << x << endl;
	return 0;
}

int main(){
	int t;
	cin >> t;
	for(int i=0; i<t; i++){
		if(solve()<0) break;
	}

	return 0;
}
