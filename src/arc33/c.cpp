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

template <class T>
class Bit{
	vector<T> v;
	public:
	Bit(int n) {
		v = vector<T>(n);
	}
	// i must be 0 <= i < n
	T sum(int i){
		int s=0;
		while(i>0){
			s += v[i];
			i -= i & -i;
		}
		return s;
	}
	// i must be 1 <= i < n
	void add(int i, T x){
		while(i <= v.size()){
			v[i] += x;
			i += i & -i;
		}
	}
};

int main_(){
	Bit<int> bit(10);
	bit.add(1,10);
	bit.add(5,20);
	cout << bit.sum(0) << endl;
	cout << bit.sum(2) << endl;
	cout << bit.sum(5) << endl;
	cout << bit.sum(8) << endl;
	return 0;
}

int main(){
	int Q;
	cin >> Q;

	Bit<int> bit(200010);
	vector<int> ans;
	for(int i=0; i<Q; i++){
		int T, X;
		cin >> T >> X;
		if(T == 1){
			bit.add(X, 1);
		} else{
			int lb = 0, ub = 200001;
			while(ub - lb > 1){
				int mid = (lb+ub)/2;
				if(bit.sum(mid) < X){
					lb = mid;
				} else {
					ub = mid;
				}
			}
			ans.push_back(ub);
			bit.add(ub, -1);
		}
	}

	for(int i=0; i<ans.size(); i++) cout << ans[i] << endl;

	return 0;
}
