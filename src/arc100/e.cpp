#include<iostream>
#include<iomanip>
//#include<cstdio>
#include<vector>
#include<map>
#include<queue>
#include<algorithm>
#include<cmath>
#include<cassert>
#include<set>
using namespace std;
typedef long long ll;
const int pNmax = 1<<18;
int N;
ll A[pNmax];
int vec[pNmax][2];

int main(){
	cin >> N;
	for(int i=0; i<(1<<N); i++) cin >> A[i];
	for(int i=0; i<(1<<N); i++){
		vec[i][0] = vec[i][1] = -1;
	}

	vector<pair<ll, int> > t;
	set<int> s;
	for(int i=0; i<(1<<N); i++){
		s.insert(i);
		for(int k=0; k<18; k++){
			int n = i & ~(1<<k);
			//cout << i << " " << k << " " << n << endl;
			if(vec[n][0]>=0) s.insert(vec[n][0]);
			if(vec[n][1]>=0) s.insert(vec[n][1]);
		}
		for(set<int>::iterator it=s.begin(); it!=s.end(); it++){
			//cout << i << ":" << *it << " " << A[*it] << endl;
			t.push_back(make_pair(A[*it], *it));
		}
		sort(t.begin(), t.end());
		reverse(t.begin(), t.end());
		vec[i][0] = t[0].second;
		if(s.size() >= 2) vec[i][1] = t[1].second;
		s.clear();
		t.clear();
	}

	ll m = 0;
	for(int i=1; i<(1<<N); i++){
		if(A[vec[i][0]]+A[vec[i][1]] > m) m = A[vec[i][0]]+A[vec[i][1]];
		cout << m << endl;
	}

	return 0;
}
