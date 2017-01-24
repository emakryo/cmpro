#include<iostream>
#include<iomanip>
#include<algorithm>
#include<vector>
#include<queue>
#include<map>
#include<cmath>
using namespace std;
typedef long long ll;
map<ll, int> dist;

void decode(ll x, int y[8]){
	for(int i=0; i<8; i++){
		y[7-i] = x%10;
		x /= 10;
	}
}

ll encode(int x[8]){
	ll y = 0;
	for(int i=0; i<8; i++){
		y *= 10;
		y += x[i];
	}
	return y;
}

int zero(ll x){
	for(int i=0; i<8; i++){
		if(x%10 == 0) return 7-i;
		x /= 10;
	}
	return -1;
}

ll swap(ll x, ll i, ll j){
	int y[8];
	decode(x, y);
	int tmp = y[i];
	y[i] = y[j];
	y[j] = tmp;
	return encode(y);
}

int main(){

	queue<pair<ll, int> > que;
	que.push(make_pair(1234567, 0));

	while(!que.empty()){
		ll x = que.front().first;
		ll t = que.front().second;
		que.pop();
		if(dist.find(x) != dist.end()) continue;
		dist[x] = t;
		int z = zero(x);
		if(z==0){
			que.push(make_pair(swap(x, 0, 1), t+1));
			que.push(make_pair(swap(x, 0, 4), t+1));
		}
		else if(z == 1){
			que.push(make_pair(swap(x, 1, 0), t+1));
			que.push(make_pair(swap(x, 1, 2), t+1));
			que.push(make_pair(swap(x, 1, 5), t+1));
		}
		else if(z == 2){
			que.push(make_pair(swap(x, 2, 1), t+1));
			que.push(make_pair(swap(x, 2, 3), t+1));
			que.push(make_pair(swap(x, 2, 6), t+1));
		}
		else if(z == 3){
			que.push(make_pair(swap(x, 3, 2), t+1));
			que.push(make_pair(swap(x, 3, 7), t+1));
		}
		else if(z == 4){
			que.push(make_pair(swap(x, 4, 0), t+1));
			que.push(make_pair(swap(x, 4, 5), t+1));
		}
		else if(z == 5){
			que.push(make_pair(swap(x, 5, 1), t+1));
			que.push(make_pair(swap(x, 5, 4), t+1));
			que.push(make_pair(swap(x, 5, 6), t+1));
		}
		else if(z == 6){
			que.push(make_pair(swap(x, 6, 2), t+1));
			que.push(make_pair(swap(x, 6, 5), t+1));
			que.push(make_pair(swap(x, 6, 7), t+1));
		}
		else if(z == 7){
			que.push(make_pair(swap(x, 7, 3), t+1));
			que.push(make_pair(swap(x, 7, 6), t+1));
		}
	}

	int x[8];
	ll y;
	while(cin >> x[0]){
		for(int i=1; i<8; i++) cin >> x[i];
		y = 0;
		for(int i=0; i<8; i++){
			y *= 10;
			y += x[i];
		}
		//cout << y << endl;
		cout << dist[y] << endl;
	}

	return 0;
}
