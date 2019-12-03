#include<bits/stdc++.h>

struct rational {
	typedef long long ll;
	ll d, n;
	rational(ll denominator=0, ll nominator=1): d(denominator), n(nominator) {}
	// Caution: overflow
	bool operator< (const rational &o) const { return d*o.n<o.d*n; }
	bool operator== (const rational &o) const { return d*o.n==o.d*n; }
	double operator()() const { return (double)d/n; }
};
