#include<iostream>
#include<iomanip>
#include<vector>
#include<map>
#include<queue>
#include<algorithm>
#include<cmath>
using namespace std;
typedef long long ll;
const int Nmax = 300000;
int N,M,L[Nmax],R[Nmax];

template <class T>
class Bit{
	vector<T> v;
	public:
	Bit(int n) {
		v = vector<T>(n);
	}
	T sum(int i){
		int s=0;
		while(i>0){
			s += v[i];
			i -= i & -i;
		}
		return s;
	}

	void add(int i, T x){
		while(i <= v.size()){
			v[i] += x;
			i += i & -i;
		}
	}
};

int main(){
	cin >> N >> M;
	for(int i=0; i<N; i++) cin >> L[i] >> R[i];

	vector<pair<int, int> > vec;
	for(int i=0; i<N; i++){
		vec.push_back(make_pair(R[i]-L[i]+1, i));
	}
	sort(vec.begin(), vec.end());

	vector<pair<int, int> >::iterator j=vec.begin();
	Bit<int> cnt(M+1);
	for(int i=1; i<=M; i++){
		while(j != vec.end() && j->first < i){
			cnt.add(L[j->second], 1);
			if(R[j->second]+1<=M)
				cnt.add(R[j->second]+1, -1);
			j++;
		}
		int ans = vec.end()-j;
		for(int j=0; i*j<=M; j++){
			ans += cnt.sum(i*j);
		}
		cout << ans << endl;
	}



	return 0;
}
