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
	int na = count(s.begin(), s.end(), 'a');
	cout << min((int)s.size(), 2*na-1) << endl;;

	return 0;
}
