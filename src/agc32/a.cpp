#include<iostream>
#include<iomanip>
//#include<cstdio>
#include<vector>
#include<list>
#include<map>
#include<queue>
#include<algorithm>
#include<cmath>
#include<cassert>
using namespace std;
typedef long long ll;
const int Nmax = 100;
int N;
int B[Nmax];

int main(){
	cin >> N;
	for(int i=0; i<N; i++) cin >> B[i];

	vector<int> ans;

	list<int> x(B, B+N);
	for(int i=0; i<N; i++){
		//for(auto j=x.begin(); j!=x.end();) cout << *j << (++j==x.end()?'\n': ' ');
		int k=N-i;
		auto t=x.rend();
		for(auto j=x.rbegin(); j!=x.rend(); j++){
			if(*j==k){
				t = j;
				break;
			}
			//cout << k << " " << *j << endl;
			k--;
		}
		if(t==x.rend()) break;
		//cout << k << " " << *t << endl;
		if(t==x.rbegin()){
			//cout << "last " << *t << endl;
			x.pop_back();
		} else {
			t++;
			x.erase(t.base());
		}
		ans.push_back(k);
	}
	reverse(ans.begin(), ans.end());

	if(ans.size()==N){
		for(int i=0; i<N; i++){
			cout << ans[i] << endl;
		}
	} else {
		cout << -1 << endl;
	}

	return 0;
}
