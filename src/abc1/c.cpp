#include<iostream>
#include<iomanip>
#include<algorithm>
#include<vector>
#include<queue>
#include<map>
#include<cmath>
using namespace std;
typedef long long ll;
int deg, dis;

int main(){
	cin >> deg >> dis;

	string dir;
	deg *= 10;
	if(1125 <= deg && deg < 3375){
		dir = "NNE";
	}
	else if(3375 <= deg && deg < 5625){
		dir = "NE";
	}
	else if(5625 <= deg && deg < 7875){
		dir = "ENE";
	}
	else if(7875 <= deg && deg < 10125){
		dir = "E";
	}
	else if(10125 <= deg && deg < 12375){
		dir = "ESE";
	}
	else if(12375 <= deg && deg < 14625){
		dir = "SE";
	}
	else if(14625 <= deg && deg < 16875){
		dir = "SSE";
	}
	else if(16875 <= deg && deg < 19125){
		dir = "S";
	}
	else if(19125 <= deg && deg < 21375){
		dir = "SSW";
	}
	else if(21375 <= deg && deg < 23625){
		dir = "SW";
	}
	else if(23625 <= deg && deg < 25875){
		dir = "WSW";
	}
	else if(25875 <= deg && deg < 28125){
		dir = "W";
	}
	else if(28125 <= deg && deg < 30375){
		dir = "WNW";
	}
	else if(30375 <= deg && deg < 32625){
		dir = "NW";
	}
	else if(32625 <= deg && deg < 34875){
		dir = "NNW";
	}
	else dir = "N";

	int w;
	double speed = (double)dis/60;
	if(speed < 0.25) w = 0;
	else if(speed < 1.55) w = 1;
	else if(speed < 3.35) w = 2;
	else if(speed < 5.45) w = 3;
	else if(speed < 7.95) w = 4;
	else if(speed < 10.75) w = 5;
	else if(speed < 13.85) w = 6;
	else if(speed < 17.15) w = 7;
	else if(speed < 20.75) w = 8;
	else if(speed < 24.45) w = 9;
	else if(speed < 28.45) w = 10;
	else if(speed < 32.65) w = 11;
	else w = 12;

	if(w == 0) dir = "C";
	cout << dir << " " << w << endl;

	return 0;
}
