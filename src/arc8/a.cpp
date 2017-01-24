#include<iostream>
#include<iomanip>
#include<algorithm>
#include<vector>
#include<queue>
#include<map>
#include<cmath>
using namespace std;
typedef long long ll;

int main(){
	int N;
	cin >> N;
	cout << min(N%10==0 ? 100*(N/10) : 100*(N/10+1),
			100*(N/10)+(N%10)*15) << endl;
	return 0;
}
