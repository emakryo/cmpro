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
const int Nmax = 1e5;
int N, X[Nmax], Y[Nmax];

void rec(vector<pair<int, int> > &vec, int l, int r, vector<pair<int, int> > &ans){
	if(r-l <= 1) return;
	int x = vec[(l+r)/2].first;
	vector<int> ys_add;
	vector<int> ys_ignore;
	for(int i=l; i<r; i++){
		if(vec[i].first != x){
			ys_add.push_back(vec[i].second);
		}
		else{
			ys_ignore.push_back(vec[i].second);
		}
	}
	sort(ys_add.begin(), ys_add.end());
	vector<int>::iterator last = unique(ys_add.begin(), ys_add.end());

	for(vector<int>::iterator i=ys_add.begin(); i!=last; i++){
		if(!binary_search(ys_ignore.begin(), ys_ignore.end(), *i)){
			ans.push_back(make_pair(x, *i));
		}
	}

	int rl = (l+r)/2;
	while(rl > l && vec[rl-1].first == x) rl--;
	rec(vec, l, rl, ans);

	int lr = (l+r)/2;
	while(lr < r && vec[lr].first == x) lr++;
	rec(vec, lr, r, ans);
}


int main(){
	cin >> N;
	for(int i=0; i<N; i++){
		cin >> X[i] >> Y[i];
	}

	vector<pair<int, int> > given(N);
	for(int i=0; i<N; i++){
		given[i] = make_pair(X[i], Y[i]);
	}
	sort(given.begin(), given.end());

	vector<pair<int, int> > answer;
	rec(given, 0, N, answer);

	cout << answer.size() << endl;
	for(int i=0; i<answer.size(); i++){
		cout << answer[i].first << " " << answer[i].second << endl;
	}

	return 0;
}
