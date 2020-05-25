#include<bits/stdc++.h>

struct rational {
	typedef long long ll;
	ll d, n;
	rational(ll denominator=0, ll nominator=1){
		d = denominator;
		n = nominator;
		if(d == 0) n = 1;
		else {
			ll g = gcd(abs(d), abs(n));
			d /= g; n /= g;
		}

		if(n<0){ d=-d; n=-n; }
	}
	rational(std::pair<ll, ll> p): rational(p.first, p.second) {}
	// Caution: overflow
	bool operator< (const rational &o) const {
		return d*o.n<n*o.d;
		//return double(*this)<double(o);
	}
	bool operator== (const rational &o) const { return d==o.d&&n==o.n; }
	rational inv() const { return rational(n, d); }
	rational operator- () const { return rational(-d, n); }
	operator double() const { return (double)d/n; }
	operator std::pair<ll, ll>() const {return {d, n};}
	ll gcd(ll x, ll y){
		if(y==0) return x;
		else return gcd(y, x%y);
	}
};
