#include<bits/stdc++.h>
#include<boost/variant.hpp>
using namespace std;
typedef long long ll;
typedef vector<boost::variant<bool, ll, int, string, double, char*, const char*>> any;
template<typename T> inline void pr(const vector<T> &xs){
	for(int i=0; i<xs.size()-1; i++) cout<<xs[i]<<" ";
	(xs.empty()?cout:(cout<<xs[xs.size()-1]))<<endl;
}
#ifdef DEBUG
#define debug(...) pr(any{__VA_ARGS__})
#define debugv(x) pr((x))
#else
#define debug(...)
#define debugv(x)
#endif

int main(){
	int K;
	cin >> K;

	vector<int> x(1, 1);
	for(int i=1; i<K; i++){
		int k = 0;
		while(k<x.size()-1 && (x[k]==x[k+1]+1 || x[k]==9)) k++;
		if(x[k]==9){
			x.push_back(1);
			x[k] = 0;
		} else {
			x[k]++;
		}

		for(int j=k-1; j>=0; j--) x[j]=max(0, x[j+1]-1);

		/*
		for(int i=x.size()-1; i>=0; i--) cout << x[i];
		cout << endl;
		*/
	}
	for(int i=x.size()-1; i>=0; i--) cout << x[i];
	cout << endl;

	return 0;
}
