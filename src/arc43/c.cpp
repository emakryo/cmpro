#include<iostream>
#include<iomanip>
//#include<cstdio>
#include<vector>
#include<map>
#include<queue>
#include<algorithm>
#include<cmath>
#include<set>
#include<cassert>
using namespace std;
typedef long long ll;

template <class T>
class Bit{
	vector<T> v;
	public:
	Bit(int n) {
		v = vector<T>(n);
	}
	// i must be 0 <= i < n
	T sum(int i){
		T s=0;
		while(i>0){
			s += v[i];
			i -= i & -i;
		}
		return s;
	}
	// i must be 1 <= i < n
	void add(int i, T x){
		while(i < v.size()){
			v[i] += x;
			i += i & -i;
		}
	}
};

// v: permutation of (1, ... , n)
int crossing(vector<int> &v){
	Bit<int> bit(v.size()+1);
	int count = 0;
	for(int i=0; i<v.size(); i++){
		count += i - bit.sum(v[i]);
		bit.add(v[i], 1);
	}
	return count;
}

int main(){
	int N;
	cin >> N;
	vector<int> A(N), B(N);
	for(int i=0; i<N; i++){
		cin >> A[i];
		A[i]--;
	}
	for(int i=0; i<N; i++){
		cin >> B[i];
		B[i]--;
	}

	vector<int> Aidx(N);
	for(int i=0; i<N; i++) Aidx[A[i]]=i;
	Bit<int> atob(N+1);
	ll cross = 0;
	for(int i=0; i<N; i++){
		cross += Aidx[B[i]]-atob.sum(1+Aidx[B[i]]);
		//cout << Aidx[B[i]] << " " <<atob.sum(1+Aidx[B[i]]) << endl;
		atob.add(1+Aidx[B[i]], 1);
	}
	//cout << cross << endl;
	//

	if(cross%2){
		cout << -1 << endl;
		return 0;
	}

	ll cross2 = 0;
	vector<int> ans;
	set<int> used;
	atob = Bit<int>(N+1);
	for(int i=0; i<N; i++){
		if(cross2 + Aidx[B[i]]-atob.sum(1+Aidx[B[i]]) <= cross/2){
			cross2 += Aidx[B[i]]-atob.sum(1+Aidx[B[i]]);
			atob.add(1+Aidx[B[i]], 1);
			ans.push_back(B[i]);
			used.insert(B[i]);
		} else {
			int k;
			for(int j=0; j<N; j++){
				if(used.find(A[j]) == used.end()){
					ans.push_back(A[j]);
					if(A[j]==B[i]) k=ans.size()-1;
				}
			}
			for(int j=0; j<cross/2-cross2; j++){
				swap(ans[k], ans[k-1]);
				k--;
			}
			break;
		}
	}

	for(int i=0; i<N; i++) cout << 1+ans[i] << (i==N-1?'\n':' ');

	return 0;
}
