#include<bits/stdc++.h>
#include<boost/variant.hpp>
using namespace std;
typedef long long ll;
typedef vector<boost::variant<bool, ll, int, string, double>> any;
template<typename T> inline void pr(const vector<T> &xs){
	if(xs.empty()){
		cout << endl;
	} else {
		for(int i=0; i<xs.size()-1; i++) cout << xs[i] << " ";
		cout << xs[xs.size()-1] << endl;
	}
}
template<typename T> inline void debug(const vector<T> &xs){
#ifdef DEBUG
	pr(xs);
#endif
}

ll gcd(ll x, ll y){
	if(y==0) return x;
	else return gcd(y, x%y);
}

int main(){
	int N;
	cin >> N;

	vector<int> x;
	for(int i=2; i<31; i++){
		if((i%2==0||i%3==0||i%5==0)&&i!=15) x.push_back(i);
	}
	debug(x);
	debug(any{(int)x.size()});

	vector<int> small(x.size()+1);

	for(int i=1; i<(1<<x.size()); i++){
		int sum = 0;
		int nbit = 0;
		for(int k=0; k<x.size(); k++){
			if((i>>k)&1){
				sum += x[k];
				nbit++;
			}
		}
		if(sum%30!=0) continue;
		bool ok = true;
		int g = -1;
		for(int k=0; k<x.size(); k++){
			if((i>>k)&1){
				if(gcd(sum-x[k], x[k])==1){
					ok = false;
					break;
				}
				if(g<0) g=x[k];
				else g=gcd(g, x[k]);
			}
		}
		if(ok&&g==1||nbit<3) small[nbit] = i;
	}

	debug(small);

#ifdef DEBUG
	for(int i=0; i<=x.size(); i++){
		vector<int> a;
		for(int k=0; k<x.size(); k++){
			if((small[i]>>k)&1) a.push_back(x[k]);
		}
		debug(a);
	}
#endif

	int mod = (N-1)%x.size()+1;
	int rep = (N-1)/x.size();

	vector<int> ans;
	for(int k=0; k<x.size(); k++){
		if((small[mod]>>k)&1) ans.push_back(x[k]);
	}
	for(int i=0; i<rep; i++){
		for(int j: x){
			ans.push_back(j+30*(i+1));
		}
	}

	pr(ans);

	return 0;
}
