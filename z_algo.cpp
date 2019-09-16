#include<bits/stdc++.h>

// Z array: Z[i] = maximum n s.t. str[0..n] == str[i..i+n]
std::vector<int> getZarray(std::string str) {
	int n = str.length();
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
			while (R<n && str[R-L] == str[R]) R++;
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
				while (R<n && str[R-L] == str[R]) R++;
				Z[i] = R-L;
				R--;
			}
		}
	}
	return Z;
}
