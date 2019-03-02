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
	string s;
	cin >> s;
	int x = 0;
	for(int i=0; i<s.size(); i++){
		if(s[i]<'0' || '9'<s[i]) continue;
		x *= 10;
		x += s[i]-'0';
	}

	cout << (x <= 20190430?"Heisei":"TBD") << endl;

	return 0;
}
