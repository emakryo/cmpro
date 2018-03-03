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
	map<string, int> m;
	cin >> n;
	for(int i=0; i<n; i++){
		string s;
		cin >> s;
		m[s]++;
	}
	int n_max = 0;
	string s_max;
	for(auto i=m.begin(); i!=m.end(); i++){
		if(n_max < i->second){
			n_max = i->second;
			s_max = i->first;
		}
	}
	cout << s_max << endl;

	return 0;
}
