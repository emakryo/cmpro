#include<iostream>
#include<algorithm>
#include<queue>
#include<vector>
#include<map>
using namespace std;
const int INF = 1e7;
bool is_prime[10000];
int primes[10000];
vector<int> graph[10000];

int eratosthenes(int n){
	int k=0;
	is_prime[2]=1;
	primes[0]=2;
	for(int p=3; p<n; p+=2){
		is_prime[p]=1;
		for(int i=0; i<k; i++){
			if(p%primes[i] == 0){
				is_prime[p] = 0;
				break;
			}
		}
		if(is_prime[p]){
			primes[k++] = p;
		}
	}
	return k;
}

int main(){
	int upper = eratosthenes(10000);
	int lower = lower_bound(primes, primes+upper, 1000)-primes;

	//cout << primes[lower] << " " << primes[upper-1] << endl;

	for(int i=lower; i<upper; i++){
		int p = primes[i];
		int dk=1;
		for(int k=0; k<4; k++){
			for(int j=0; j<10; j++){
				if(k==3 && j==0) continue;
				int s = p - (p/dk-p/(dk*10)*10)*dk + j*dk;
				if(is_prime[s] && s!=p){
					//cout << p << " " << s << " " << endl;
					graph[p].push_back(s);
				}
			}
			dk *= 10;
		}
	}

	int N, p, q;
	cin >> N;
	for(int i=0; i<N; i++){
		cin >> p >> q;

		vector<int> dist(10000,INF);
		queue<pair<int, int> > que;
		que.push(make_pair(0, p));
		dist[p] = 0;
		while(!que.empty()){
			int d = que.front().first;
			int r = que.front().second;
			que.pop();
			if(r == q) break;
			for(int i=0; i<graph[r].size(); i++){
				if(dist[graph[r][i]] < INF) continue;
				dist[graph[r][i]] = d+1;
				que.push(make_pair(d+1,graph[r][i]));
			}
		}

		if(dist[q] == INF) cout << "Impossible" << endl;
		else cout << dist[q] << endl;

	}

	return 0;
}
