#include<cstdio>
#include<algorithm>
#include<vector>
#include<queue>
#include<map>
#include<cmath>
using namespace std;
typedef long long ll;
const int Nmax = 50000;
int N;
int A[Nmax], B[Nmax];

int main(){
	scanf("%d", &N);
	for(int i=0; i<N; i++) scanf("%d%d", &A[i], &B[i]);

	vector<pair<int, int> > vec;
	for(int i=0; i<N; i++){
		vec.push_back(make_pair(A[i], -i-1));
		vec.push_back(make_pair(B[i], i+1));
	}
	sort(vec.begin(), vec.end());

	int ans = 0;
	int cur = 0;
	for(int i=0; i<vec.size(); i++){
		if(vec[i].second < 0){
			cur += 1;
			ans = max(ans, cur);
		}
		else {
			cur -= 1;
		}
	}
	printf("%d\n", ans);

	queue<int> avail;
	for(int i=0; i<ans; i++){
		avail.push(i+1);
	}
	vector<int> alloc(N);
	for(int i=0; i<vec.size(); i++){
		if(vec[i].second < 0){
			alloc[-vec[i].second-1] = avail.front();
			avail.pop();
			//printf("<%d %d\n", alloc[-vec[i].second-1], -vec[i].second-1);
		}
		else{
			//printf(">%d %d\n", alloc[vec[i].second-1], vec[i].second-1);
			avail.push(alloc[vec[i].second-1]);
		}
	}

	for(int i=0; i<N; i++){
		printf("%d\n", alloc[i]);
	}

	return 0;
}
