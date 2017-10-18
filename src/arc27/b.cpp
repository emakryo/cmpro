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

class UnionFind{
	vector<int> par, rnk;
	public:
	UnionFind(int n){
		par=vector<int>(n);
		rnk=vector<int>(n,0);
		for(int i=0; i<n; i++) par[i]=i;
	}
	int root(int i){
		if(par[i]==i) return i;
		return par[i]=root(par[i]);
	}
	void unite(int i, int j){
		int ri = root(i);
		int rj = root(j);
		if(ri==rj) return;

		if(rnk[ri]==rnk[rj]){
			par[ri] = rj;
			rnk[rj]++;
		}
		else if(rnk[ri] < rnk[rj]){
			par[ri] = rj;
		}
		else{
			par[rj] = ri;
		}
	}
	bool same(int i, int j){
		return root(i) == root(j);
	}
};

bool is_digit(char c){
	return '0' <= c && c <= '9';
}

int main(){
	int N;
	string s1, s2;

	cin >> N;
	cin >> s1 >> s2;

	UnionFind uf(27);

	vector<bool> used(26);
	for(int i=0; i<N; i++){
		if(!is_digit(s1[i]) && !is_digit(s2[i])){
			uf.unite(s1[i]-'A', s2[i]-'A');
		}
		else if(is_digit(s1[i]) && !is_digit(s2[i])){
			uf.unite(s2[i]-'A', 26);
		}
		else if(!is_digit(s1[i]) && is_digit(s2[i])){
			uf.unite(s1[i]-'A', 26);
		}

		if(!is_digit(s1[i])){
			used[s1[i]-'A'] = true;
		}
		if(!is_digit(s2[i])){
			used[s2[i]-'A'] = true;
		}
	}

	for(int i=0; i<26; i++){
		for(int j=i+1; j<26; j++){
			if(uf.same(i, j)){
				used[j] = false;
			}
		}
		if(uf.same(i, 26)){
			used[i] = false;
		}
	}


	int n = 0;
	for(int i=0; i<26; i++){
		n += used[i] ? 1 : 0;
	}


	ll x = 1;
	if(s1[0] != s2[0] && !is_digit(s1[0]) && used[s1[0]-'A'] && !is_digit(s2[0]) && used[s2[0]-'A']){
		x *= 81;
		n -= 2;
	}
	else if(!is_digit(s1[0]) && used[s1[0]-'A'] || !is_digit(s2[0]) && used[s2[0]-'A']){
		x *= 9;
		n--;
	}

	for(int i=0; i<n; i++) x *= 10;
	cout << x << endl;

	return 0;
}
