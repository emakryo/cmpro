#include<iostream>
#include<iomanip>
//#include<cstdio>
#include<vector>
#include<map>
#include<set>
#include<queue>
#include<algorithm>
#include<cmath>
#include<cassert>
using namespace std;
typedef long long ll;

int main(){
	ll n;
	cin >> n;
	set<ll> s;
	s.insert(n);
	while(true){
		n++;
		while(n%10==0) n/=10;
		if(s.find(n)!=s.end()) break;
		//cout << n << endl;
		s.insert(n);
	}
	cout << s.size() << endl;


	return 0;
}
