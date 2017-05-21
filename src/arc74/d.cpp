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
int N;
ll A[3*Nmax];

int main(){
	cin >> N;
	for(int i=0; i<3*N; i++) cin >> A[i];

	priority_queue<pair<ll, int>, vector<pair<ll, int> >, greater<pair<ll, int> > > former;
	priority_queue<pair<ll, int>, vector<pair<ll, int> >, greater<pair<ll, int> > > latter;
	vector<bool> in_latter(3*N);

	ll former_sum = 0;
	ll latter_sum = 0;
	for(int i=0; i<N; i++){
		former.push(make_pair(A[i], i));
		former_sum += A[i];
	}
	for(int i=N; i<3*N; i++){
		latter.push(make_pair(A[i], i));
	}
	for(int i=0; i<N; i++){
		ll a=latter.top().first;
		int n=latter.top().second;
		latter_sum += a;
		in_latter[n] = true;
		latter.pop();
	}

	ll ans = former_sum - latter_sum;
	for(int i=N; i<2*N; i++){
		former.push(make_pair(A[i], i));
		ll a = former.top().first;
		former.pop();
		former_sum += A[i] - a;

		if(in_latter[i]){
			ll b;
			int n;
			while(!latter.empty()){
				b = latter.top().first;
				n = latter.top().second;
				latter.pop();
				if(n > i) break;
			}
			latter_sum += b - A[i];
			in_latter[n] = true;
		}

		ans = max(ans, former_sum-latter_sum);
	}

	cout << ans << endl;




	return 0;
}
