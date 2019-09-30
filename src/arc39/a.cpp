#include<bits/stdc++.h>
#include<boost/variant.hpp>
using namespace std;
typedef long long ll;
typedef vector<boost::variant<bool, ll, int, string, double, char*, const char*>> any;
template<typename T> inline void pr(const vector<T> &xs){
	for(int i=0; i<xs.size()-1; i++) cout<<xs[i]<<" ";
	(xs.empty()?cout:(cout<<xs[xs.size()-1]))<<endl;
}
#ifdef DEBUG
#define debug(...) pr(any{__VA_ARGS__})
#define debugv(x) pr((x))
#else
#define debug(...)
#define debugv(x)
#endif

int main(){
	int A, B;
	cin >> A >> B;

	int a0 = A-(A/100)*100+900;
	int ans = a0 - B;
	int a1 = A-((A/10)%10)*10+90;
	ans = max(a1-B, ans);
	int a2 = A-A%10+9;
	ans = max(a2-B, ans);

	int b0 = B-(B/100)*100+100;
	ans = max(A-b0, ans);
	int b1 = B-((B/10)%10)*10;
	ans = max(A-b1, ans);
	int b2 = B-B%10;
	ans = max(A-b2, ans);

	cout << ans << endl;

	return 0;
}
