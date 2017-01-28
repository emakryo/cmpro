#include<iostream>
#include<iomanip>
#include<vector>
#include<map>
#include<queue>
#include<algorithm>
#include<cmath>
using namespace std;
typedef long long ll;
string board[19];

bool win(string b[19], char c){
	for(int i=0; i<19; i++){
		for(int j=0; j<19; j++){
			if(b[i][j] != c) continue;
			int dx[] = {1,0,1,-1};
			int dy[] = {0,1,1,1};
			for(int k=0; k<4; k++){
				int l = 1;
				while(i+l*dx[k] >= 0 && i+l*dx[k]<19 && j+l*dy[k]<19 && b[i+l*dx[k]][j+l*dy[k]]==c) l++;
				if(l>=5) return true;
			}
		}
	}

	return false;
}

int main(){
	int black=0, white=0;
	for(int i=0; i<19; i++){
		cin >> board[i];
		for(int j=0; j<19; j++){
			if(board[i][j] == 'o') black++;
			if(board[i][j] == 'x') white++;
		}
	}

	if(black < white || black > white+1){
		cout << "NO" << endl;
		return 0;
	}

	if(black == white){
		if(win(board, 'o')){
			cout << "NO" << endl;
			return 0;
		}
		if(win(board, 'x')){
			for(int i=0; i<19; i++){
				for(int j=0; j<19; j++){
					if(board[i][j] != 'x') continue;
					board[i][j]='.';
					if(!win(board, 'x')){
						cout << "YES" << endl;
						return 0;
					}
					board[i][j]='x';
				}
			}
			cout << "NO" << endl;
			return 0;
		}
		cout << "YES" << endl;
		return 0;
	}

	if(win(board, 'x')){
		cout << "NO" << endl;
		return 0;
	}
	if(win(board, 'o')){
		for(int i=0; i<19; i++){
			for(int j=0; j<19; j++){
				if(board[i][j] != 'o') continue;
				board[i][j] = '.';
				if(!win(board, 'o')){
					cout << "YES" << endl;
					return 0;
				}
				board[i][j] = 'o';
			}
		}
		cout << "NO" <<endl;
		return 0;
	}
	cout << "YES" << endl;
	return 0;
}
