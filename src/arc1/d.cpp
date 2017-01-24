#include<iostream>
#include<iomanip>
#include<algorithm>
#include<vector>
#include<queue>
#include<deque>
#include<map>
#include<cmath>
using namespace std;
typedef long long ll;
const int Nmax = 2000001;
ll N, S, G;
ll L[Nmax], R[Nmax];

ll ccw(ll ax, ll ay, ll bx, ll by, ll cx, ll cy){
	return (bx-ax)*(cy-by) - (by-ay)*(cx-bx);
}

int main(){
	cin >> N >> S >> G;
	for(int i=0; i<=N; i++){
		cin >> L[i] >> R[i];
	}

	L[0] = R[0] = S;
	L[N] = R[N] = G;

	double ans = 0;
	ll x = S;
	deque<ll> left, right;
	left.push_back(0);
	left.push_back(1);
	right.push_back(0);
	right.push_back(1);

	for(int i=2; i<=N; i++){
		while(left.size() > 1){
			ll j = left.back();
			ll k = left[left.size()-2];
			ll x0 = left.size() == 2 ? x : L[k];
			if(ccw(x0, k, L[j], j, L[i], i) > 0){
				break;
			}
			left.pop_back();
		}
		left.push_back(i);

		while(right.size() > 1){
			ll j = right.back();
			ll k = right[right.size()-2];
			ll x0 = right.size() == 2 ? x : R[k];
			if(ccw(x0, k, R[j], j, R[i], i) < 0){
				break;
			}
			right.pop_back();
		}
		right.push_back(i);

		while(ccw(x, left.front(),
					L[left[1]], left[1],
					R[right[1]], right[1]) > 0){
			ll y = left.front();
			ll nx, ny;
			if(left[1] < right[1]){
				ny = left[1];
				nx = L[ny];
				left.pop_front();
				right.pop_front();
				right.push_front(ny);
			}
			else{
				ny = right[1];
				nx = R[ny];
				right.pop_front();
				left.pop_front();
				left.push_front(ny);
			}
			//cout << "[" << x << " " << y << "]" << endl;
			ans += sqrt((nx-x)*(nx-x)+(ny-y)*(ny-y));
			x = nx; y = ny;
		}
		/*
		cout << i << " " << x << " " << endl;
		for(int j=0; j<left.size(); j++) cout << left[j] <<" ";
		cout << endl;
		for(int j=0; j<right.size(); j++) cout << right[j] <<" ";
		cout << endl;
		cout << endl;
		*/
	}

	ll y = left[0];
	//cout << "[" << x << " " << y << "]" << endl;
	ans += sqrt((x-G)*(x-G)+(y-N)*(y-N));

	cout << fixed << setprecision(15) << ans << endl;

	return 0;
}
