#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll A, B;

int main(){
	cin >> A >> B;

	if(A<0&&0<B) cout << (B-A-1) << endl;
	else cout << B-A << endl;

	return 0;
}
