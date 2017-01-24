#include<iostream>
#include<iomanip>
#include<algorithm>
#include<vector>
#include<queue>
#include<map>
#include<cmath>
using namespace std;
typedef long long ll;
int R,G,B;

int main(){
	cin >> R >> G >> B;

	int ans = 1e8;
	for(int i=-300; i<300; i++){
		int gr = i+G/2;
		int gl = i-(G-G/2-1);
		int g;
		if(gl<=0 && 0<=gr){
			g = (-gl)*(-gl+1)/2+gr*(gr+1)/2;
		}
		else if(gr<=0){
			g = (-gl)*(-gl+1)/2-(-gr-1)*(-gr)/2;
		}
		else if(gl>=0){
			g = gr*(gr+1)/2-gl*(gl-1)/2;
		}

		int rr,rl,r;
		if((R-1)/2-100 < gl){
			rr = -100+(R-1)/2;
			rl = -100-(R-(R-1)/2-1);
		}
		else{
			rr = gl-1;
			rl = rr-R+1;
		}
		if(rl<=-100 && -100<=rr){
			r = (rr+100)*(rr+101)/2+(-100-rl)*(-99-rl)/2;
		}
		else if(rr<=-100){
			r = (-rl-100)*(-rl-99)/2-(-rr-101)*(-rr-100)/2;
		}
		else if(rl>=-100){
			r = (rr+100)*(rr+101)/2-(rl+100)*(rl+99)/2;
		}

		int br, bl, b;
		if(gr < 100-(B-1)/2){
			bl = 100-(B-1)/2;
			br = 100+(B-1-(B-1)/2);
		}
		else{
			bl = gr+1;
			br = bl+B-1;
		}
		if(bl<=100 && 100<=br){
			b = (br-100)*(br-99)/2+(100-bl)*(101-bl)/2;
		}
		else if(br<=100){
			b = (-bl+100)*(-bl+101)/2-(-br+99)*(-br+100)/2;
		}
		else if(bl>=100){
			b = (br-100)*(br-99)/2-(bl-100)*(bl-101)/2;
		}

		/*
		cout << rl << " " << rr << " ";
		cout << gl << " " << gr << " ";
		cout << bl << " " << br << " ";
		cout << r << " " << g << " " << b << endl;
		*/

		ans = min(ans, r+b+g);
	}
	cout << ans << endl;
	return 0;
}
