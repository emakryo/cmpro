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

pair<ll, ll> solve(){
	ll N, K;
	cin >> N >> K;
	if(N==K) return make_pair(0, 0);
	priority_queue<pair<ll, ll> > que;
	que.push(make_pair(N, 1));
	while(K>0){
		ll a = que.top().first;
		ll k = que.top().second;
		que.pop();
		while(!que.empty() && que.top().first == a){
			k += que.top().second;
			que.pop();
		}
		if(K<=k){
			return make_pair(a/2, (a-1)/2);
		}
		que.push(make_pair(a/2, k));
		que.push(make_pair((a-1)/2, k));
		K -= k;
	}
	return make_pair(0, 0);
}


int main(){
	int T;
	cin >> T;
	for(int i=0; i<T; i++){
		pair<ll, ll> p = solve();
		cout << "Case #" << (i+1) << ": " << p.first << " " << p.second << endl;;
	}

	return 0;
}
