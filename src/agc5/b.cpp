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
const int Nmax = 2e5;
int N;
int A[Nmax];

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


int main(){
    cin >> N;
    for(int i=0; i<N; i++){
        cin >> A[i];
        A[i]--;
    }

    vector<int> pos(N);
    for(int i=0; i<N; i++) pos[A[i]] = i;
    Bit<int> bit(N+1);

    ll ans = 0;
    for(int i=0; i<N-1; i++){
        int l, r;
        if(bit.sum(pos[i]+1)==0){
            l = pos[i]+1;
        } else {
            int lb = 0, ub = pos[i];
            while(ub-lb>1){
                int mid = (lb+ub)/2;
                if(bit.sum(pos[i]+1)-bit.sum(mid)>0){
                    lb = mid;
                } else {
                    ub = mid;
                }
            }
            l = pos[i]-lb;
        }
        if(bit.sum(N)-bit.sum(pos[i])==0){
            r = N-pos[i];
        } else {
            int lb = pos[i], ub = N-1;
            while(ub-lb>1){
                int mid = (lb+ub)/2;
                if(bit.sum(mid+1)-bit.sum(pos[i])>0){
                    ub = mid;
                } else {
                    lb = mid;
                }
            }
            r = ub-pos[i];
        }

    //    cout << i+1 << " " << l << " " << r << endl;
       ans += (ll)(i+1)*l*r;
       bit.add(pos[i]+1, 1);
    }
    ans += N;
    cout << ans << endl;
    return 0;
}