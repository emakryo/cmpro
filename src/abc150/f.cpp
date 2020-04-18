#include<bits/stdc++.h>
#include<boost/variant.hpp>
using namespace std;
typedef long long ll;
typedef vector<boost::variant<bool, ll, int, string, double, char*, const char*>> anys;
template<typename T> inline void pr(const vector<T> &xs){
	for(int i=0; i<xs.size(); i++) cout << xs[i] << (i==xs.size()-1?'\n':' ');
	if(xs.empty()) cout << endl;
	else cout << flush;
}
#ifdef DEBUG
#define debug(...) pr(anys{__VA_ARGS__})
#define debugv(x) pr((x))
#else
#define debug(...)
#define debugv(x)
#endif

// Z array: Z[i] = maximum n s.t. str[0..n] == str[i..i+n]
template<class It>
std::vector<int> getZarray(It begin, It end) {
	int n = end - begin;
	std::vector<int> Z(n);
	int L, R, k;
	// [L,R] make a window which matches with prefix of s
	L = R = 0;
	for (int i=1; i<n; i++) {
		// if i>R nothing matches so we will calculate.
		// Z[i] using naive way.
		if (i > R) {
			L = R = i;
			// R-L = 0 in starting, so it will start
			// checking from 0'th index. For example,
			// for "ababab" and i = 1, the value of R
			// remains 0 and Z[i] becomes 0. For string
			// "aaaaaa" and i = 1, Z[i] and R become 5
			while (R<n && begin[R-L] == begin[R]) R++;
			Z[i] = R-L;
			R--;
		} else {
			// k = i-L so k corresponds to number which
			// matches in [L,R] interval.
			k = i-L;
			// if Z[k] is less than remaining interval
			// then Z[i] will be equal to Z[k].
			// For example, str = "ababab", i = 3, R = 5
			// and L = 2
			if (Z[k] < R-i+1) Z[i] = Z[k];
			// For example str = "aaaaaa" and i = 2, R is 5,
			// L is 0
			else {
				// else start from R and check manually
				L = i;
				while (R<n && begin[R-L] == begin[R]) R++;
				Z[i] = R-L;
				R--;
			}
		}
	}
	return Z;
}

std::vector<int> occurance(std::string &text, std::string &pattern){
	std::string concat = pattern + "$" + text;
	int np = pattern.size();
	std::vector<int> z = getZarray(concat.begin(), concat.end());
	std::vector<int> idx;

	for(int i=0; i<concat.size()-np-1; i++){
		if(z[i+np+1] >= np) idx.push_back(i);
	}
	return idx;
}

int _main(){
	using namespace std;
	string text = "aababaabaacaabaa";
	string pat = "aab";
	vector<int> oc = occurance(text, pat);
	assert((oc==vector<int>{0, 5, 11}));
	return 0;
}

int main(){
	int N;
	cin >> N;
	vector<int> A(N), B(N);
	for(int i=0; i<N; i++) cin >> A[i];
	for(int i=0; i<N; i++) cin >> B[i];

	vector<bool> idx(N, true);
	for(int k=0; k<32; k++){
		string x, y;
		for(int i=0; i<N; i++) x.push_back(B[i]>>k&1);
		for(int i=0; i<N; i++) y.push_back(A[i]>>k&1);
		for(int i=0; i<N-1; i++) y.push_back(A[i]>>k&1);

		vector<int> v = occurance(y, x);
		vector<bool> bit_idx(N);
		debug(k);
		for(int a: v){
			bit_idx[a] = true;
		}

		for(int i=0; i<N; i++) x[i] = 1-(B[i]>>k&1);
		v = occurance(y, x);
		for(int a: v){
			bit_idx[a] = true;
		}
		for(int i=0; i<N; i++) idx[i] = idx[i] & bit_idx[i];
		debugv(idx);
	}

	for(int k=0; k<N; k++){
		if(idx[k]) cout << k << " " << (A[k]^B[0]) << endl;
	}

	return 0;
}
