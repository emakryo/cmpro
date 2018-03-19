#include<iostream>
#include<vector>
using namespace std;

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
		while(i <= v.size()){
			v[i] += x;
			i += i & -i;
		}
	}
};

int main(){
	Bit<int> bit(10);
	bit.add(1,10);
	bit.add(5,20);
	cout << bit.sum(0) << endl;
	cout << bit.sum(2) << endl;
	cout << bit.sum(5) << endl;
	cout << bit.sum(8) << endl;
	return 0;
}
