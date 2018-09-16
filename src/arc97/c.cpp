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
int K;
string S;

int main(){
	cin >> S >> K;
	vector<string> ss;
	for(char c='a'; c<='z'; c++){
		for(int i=0; i<S.size(); i++){
			if(S[i]!=c) continue;
			for(int j=0; j<5; j++){
				ss.push_back(S.substr(i, j+1));
			}
		}
		sort(ss.begin(), ss.end());
		auto it = unique(ss.begin(), ss.end());
		ss.resize(distance(ss.begin(), it));
		if(ss.size()>=K){
			cout << ss[K-1] << endl;
			return 0;
		}
	}


	return 0;
}
