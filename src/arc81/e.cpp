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
string A;

int main(){
	cin >> A;

	int s=0, k=0;
	vector<int> c(1, A.size());
	for(int i=A.size()-1; i>=0; i--){
		s |= 1<<(A[i]-'a');
		if(s == (1<<26)-1){
			s = 0;
			k++;
			c.push_back(i);
		}
	}

	reverse(c.begin(), c.end());
	//for(int i=0; i<c.size(); i++) cout << c[i] << endl;

	vector<vector<int> > p(26, vector<int>());
	for(int i=0; i<A.size(); i++){
		p[A[i]-'a'].push_back(i);
	}

	int n=0;
	string ans;
	for(int i=0; i<=k; i++){
		for(int j=0; j<26; j++){
			int lb=0, ub=p[j].size()-1;
			if(p[j].size() == 0 || p[j][ub] < n){
				ans.push_back('a'+j);
				break;
			}
			int l;
			if(p[j][lb]>=n) l=lb;
			else{
				while(ub-lb>1){
					int med = (lb+ub)/2;
					if(p[j][med]>=n) ub=med;
					else lb=med;
				}
				l = ub;
			}
			if(p[j][l]<c[i]) continue;
			ans.push_back('a'+j);
			n=p[j][l]+1;
			break;
		}
	}

	//cout << k+1 << endl;
	cout << ans << endl;

	return 0;
}
