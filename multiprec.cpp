// Multi precision number
// only positive numbers
// addition
#include<vector>
#include<iostream>
#include<iomanip>
#include<sstream>
using namespace std;
typedef long long ll;

class Multiprec{
	bool sign;
	ll base;
	int digit;
	vector<ll> x;
	public:
		Multiprec(ll n = 0) {
			x.push_back(n);
			digit = 18;
			base = 1e18;
			sign = true;
		}
		Multiprec add(const Multiprec&);
		Multiprec operator+ (const Multiprec&);
		Multiprec operator+ (const ll&);
		void operator+= (const Multiprec&);
		void operator+= (const ll&);
		void normalize();
		string to_string();
		void print();
};

Multiprec Multiprec::add(const Multiprec &y){
	int nx = x.size();
	int ny = y.x.size();

	Multiprec z;
	z.x = vector<ll>(max(nx, ny));
	for(int i=0; i<z.x.size(); i++){
		if(i<nx && i<ny){
			z.x[i] = x[i] + y.x[i];
		}
		else if(i<nx){
			z.x[i] = x[i];
		}
		else if(i<ny){
			z.x[i] = y.x[i];
		}
		else{
			z.x[i] = 0;
		}
	}

	z.normalize();
	return z;
}

Multiprec Multiprec::operator+ (const Multiprec &y){
	return this->add(y);
}

void Multiprec::operator+= (const Multiprec &y){
	x = add(y).x;
}

Multiprec Multiprec::operator+ (const ll &y){
	return this->add(Multiprec(y));
}

void Multiprec::operator+= (const ll &y){
	x = add(Multiprec(y)).x;
}

Multiprec operator+ (ll x, Multiprec &y){
	Multiprec z = y + x;
	return z;
}

void Multiprec::normalize(){
	int carry = 0;
	for(int i=0; i<x.size(); i++){
		x[i] += carry;
		carry = x[i] / base;
		x[i] %= base;
	}
	if(carry > 0){
		x.push_back(carry);
	}

	for(int i=x.size()-1; i>=0; i--){
		if(x[i] == 0){
			x.pop_back();
			return;
		}
	}
}

string Multiprec::to_string(){
	string s;
	for(int i=0; i<x.size(); i++){
		string t;
		stringstream ss;
		if(i != x.size()-1){
			ss << setw(digit) << setfill('0');
		}
		ss << x[i];
		ss >> t;
		s = t + s;
	}
	return s;
}

void Multiprec::print(){
	for(int i=0; i<x.size(); i++){
		cout << i << " " << x[i] << endl;
	}
}


int main(){
	Multiprec x = (ll)(1e18)+1;
	Multiprec y(1L<<60);

	Multiprec z = 0;
	for(int i=0; i<10; i++){
		z += x;
	}
	cout << x.to_string() << endl;
	cout << z.to_string() << endl;
	cout << ((ll)(1e18)+1)*10 << endl;
	return 0;
}
