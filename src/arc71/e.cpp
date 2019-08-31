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
string S, T;
const int Qmax = 1e5;
int Q;

int main(){
	cin >> S >> T >> Q;
	vector<int> ns(S.size()+1), nt(T.size()+1);
	for(int i=0; i<S.size(); i++) ns[i+1] = ns[i]+(S[i]=='A'?1:0);
	for(int i=0; i<T.size(); i++) nt[i+1] = nt[i]+(T[i]=='A'?1:0);

	for(int i=0; i<Q; i++){
		int a, b, c, d;
		cin >> a >> b >> c >> d;
		int x = b-a+1 - 2*(ns[b]-ns[a-1]);
		int y = d-c+1 - 2*(nt[d]-nt[c-1]);
		if((x+300000)%3==(y+300000)%3) cout << "YES" << endl;
		else cout << "NO" << endl;
	}

	return 0;
}
