#include<cstdio>
#include<algorithm>
#include<vector>
#include<queue>
#include<map>
#include<cmath>
using namespace std;
typedef long long ll;
const int Nmax = 1000;
int N, K;
ll A[Nmax], B[Nmax];

bool possible(double lower){
	vector<double> vec;
	for(int i=0; i<N; i++){
		vec.push_back(100*A[i] - lower*B[i]);
	}
	sort(vec.begin(), vec.end());

	double sum = 0;
	for(int i=K; i<N; i++){
		sum += vec[i];
	}

	return sum >= 0;
}


int main(){
	while(true){
		scanf("%d %d", &N, &K);
		if(N == 0 && K == 0) break;
		for(int i=0; i<N; i++){
			scanf("%lld", &A[i]);
		}
		for(int i=0; i<N; i++){
			scanf("%lld", &B[i]);
		}

		double lower = 0;
		double upper = 101;
		for(int i=0; i<100; i++){
			double center = (lower+upper)/2;
			if(possible(center)){
				lower = center;
			}
			else{
				upper = center;
			}
		}

		printf("%d\n", (int)round(lower));
	}
	return 0;
}
