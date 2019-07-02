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
	int x;
	cin >> x;

	int t = 0;
	vector<int> ans;
	for(int i=0; i<40; i++){
		int k = 0;
		while(x>>k) k++;
		while((x>>(k-1))&1) k--;
		if(k==0) break;
		x = x ^ ((1<<k)-1);
		ans.push_back(k);
		t++;
		//cout << x << endl;
		k=0;
		while(x>>k) k++;
		if((x^((1<<(k))-1))==0) break;
		x++;
		//cout << x << endl;
		t++;
		if((x^((1<<(k+1))-1))==0) break;
	}
	cout << t << endl;
	for(int i=0; i<ans.size(); i++) cout << ans[i] << (i==ans.size()-1?'\n':' ');

	return 0;
}
