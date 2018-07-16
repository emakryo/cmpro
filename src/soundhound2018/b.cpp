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
	int w;
	string s;
	cin >> s >> w;

	for(int i=0; i*w < s.size(); i++){
		cout << s[i*w];
	}
	cout << endl;

	return 0;
}
