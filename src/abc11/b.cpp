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
	if('a' <= s[0] && s[0] <= 'z') s[0] = s[0] + 'A'-'a';
	for(int i=1; i<s.size(); i++){
		if('A' <= s[i] && s[i] <= 'Z') s[i] = s[i] + 'a' - 'A';
	}
	cout << s << endl;

	return 0;
}
