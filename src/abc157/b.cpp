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
	vector<vector<int>> A(3, vector<int>(3));
	for(int i=0; i<3; i++) for(int j=0; j<3; j++){
		cin >> A[i][j];
	}
	int N;
	cin >> N;
	vector<int> B(N);
	for(int i=0; i<N; i++) cin >> B[i];

	bool ok = false;
	vector<vector<bool>> m(3, vector<bool>(3));
	for(int i=0; i<3; i++) for(int j=0; j<3; j++){
		for(int k=0; k<N; k++){
			if(A[i][j]==B[k]) m[i][j]=true;
		}
	}

	if(m[0][0]&&m[0][1]&&m[0][2] ||
			m[1][0]&&m[1][1]&&m[1][2] ||
			m[2][0]&&m[2][1]&&m[2][2] ||
			m[0][0]&&m[1][0]&&m[2][0] ||
			m[0][1]&&m[1][1]&&m[2][1] ||
			m[0][2]&&m[1][2]&&m[2][2] ||
			m[0][0]&&m[1][1]&&m[2][2] ||
			m[2][0]&&m[1][1]&&m[0][2]){
		cout << "Yes" << endl;
	} else {
		cout << "No" << endl;
	}

	return 0;
}
