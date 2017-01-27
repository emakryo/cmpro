#include<iostream>
#include<iomanip>
//#include<cstdio>
#include<vector>
#include<map>
#include<queue>
#include<algorithm>
#include<cmath>
using namespace std;
typedef long long ll;
const int Nmax = 1000;
string first, last;
int N;
string S[Nmax+2];

int main(){
	cin >> first >> last;
	cin >> N;
	for(int i=0; i<N; i++){
		cin >> S[i];
	}
	S[N] = first;
	S[N+1] = last;

	vector<vector<int> > graph(N+2);
	for(int i=0; i<N+2; i++){
		for(int j=i+1; j<N+2; j++){
			int cnt = 0;
			for(int k=0; k<first.size(); k++){
				if(S[i][k] != S[j][k]) cnt++;
			}
			if(cnt == 1){
				graph[i].push_back(j);
				graph[j].push_back(i);
				//cout << i << " " << j << endl;
			}
		}
	}

	queue<pair<int, int> > que;
	vector<int> from(N+2, -1);
	que.push(make_pair(N, 0));
	from[N] = N;
	while(!que.empty()){
		int s = que.front().first;
		int n = que.front().second;
		que.pop();
		if(s == N+1) break;
		for(int i=0; i<graph[s].size(); i++){
			if(from[graph[s][i]] >= 0) continue;
			que.push(make_pair(graph[s][i], n+1));
			from[graph[s][i]] = s;
		}
	}

	if(first == last){
		cout << 0 << endl;
		cout << first << endl;
		cout << first << endl;
	}

	if(from[N+1] < 0){
		cout << -1 << endl;
		return 0;
	}

	vector<int> path;
	int n = N+1;
	while(n != N){
		path.push_back(n);
		n = from[n];
	}

	cout << path.size()-1 << endl;
	cout << S[N] << endl;
	for(vector<int>::reverse_iterator i=path.rbegin(); i!=path.rend(); i++){
		cout << S[*i] << endl;
	}




	return 0;
}
