#include<iostream>
#include<algorithm>
#include <time.h>
#include<windows.h>
using namespace std;
const char wall[3]="回";
const char air[3]="  ";
const char no[3] ="×";
const char yes[3] ="十";
char nextturn[4][3] = {"→","↓","←","↑"}; 
int nextgo[4][2] = {0,2,2,0,0,-2,-2,0};
int gotoxy(int x,int y) //定位光标位置
{  
    HANDLE handle; //定义bai句柄变量duhandle
    COORD coord; //定义结构体coord (坐标系coord)
    coord.X = x; //横坐标x
    coord.Y = y; //纵坐标y
    handle = GetStdHandle(STD_OUTPUT_HANDLE); //获取控制台输出句柄(值为-11)
    SetConsoleCursorPosition(handle, coord); //移动光标
}
int mappingxy(int xy){
	return 2*xy;
}
int randturn[24][4] = {
    {0,1,2,3},
	{0,1,3,2},
	{0,2,1,3},
	{0,2,3,1},
	{0,3,1,2},
	{0,3,2,1},
	{1,0,2,3},
	{1,0,3,2},
	{1,2,0,3},
	{1,2,3,0},
	{1,3,0,2},
	{1,3,2,0},
	{2,0,1,3},
	{2,0,3,1},
	{2,1,0,3},
	{2,1,3,0},
	{2,3,0,1},
	{2,3,1,0},
	{3,0,1,2},
	{3,0,2,1},
	{3,1,0,2},
	{3,1,2,0},
	{3,2,0,1},
	{3,2,1,0}};
int startx,starty,endx,endy,getend;
int map[1000][1000];
int book[1000][1000] = {0};
void show(int n){
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			printf("%s",map[i][j] == 1?wall:air);
		}
		printf("\n");
	}	
}

void init(int n){
	startx = 1,starty = 0,endx = n - 2,endy = n - 2;
	getend= 0;
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			map[i][j] = 1;
		}
	}
}

void dfs(int x,int y,int *left,int n){
	if(*left == 0){
		return;
	}
	int randnum = rand() % 24;
	for(int i = 0; i < 4; i++){
		int tx = x + nextgo[randturn[randnum][i]][0];
		int ty = y + nextgo[randturn[randnum][i]][1];
		if(book[tx][ty] == 0 && tx > 0 && tx < n && ty > 0 && ty < n){
			map[x + (tx-x)/2][y+(ty-y)/2] = 0,gotoxy(mappingxy(y+(ty-y)/2),x + (tx-x)/2),printf("%s",air);
			Sleep(10);
			book[x + (tx-x)/2][y+(ty-y)/2] = 1;
			map[tx][ty] = 0,gotoxy(mappingxy(ty),tx),printf("%s",air);
			Sleep(10);
			book[tx][ty] = 1;
			(*left)--;
			dfs(tx,ty,left,n);
		}
	}
	return;
}

void find(int x,int y){
	if(x == endx && y == endy) getend = 1;
	if(getend) return;
	for(int i = 0; i < 4; i++){
		int tx = x + nextgo[i][0]/2;
		int ty = y + nextgo[i][1]/2;
		if(book[tx][ty]){
			gotoxy(mappingxy(ty),tx),printf("%s",nextturn[i]);
			Sleep(80);
			book[tx][ty] = 0;
			find(tx,ty);
			if(getend){
				//system("color 27"); 
				gotoxy(mappingxy(ty),tx),printf("%s",yes);
				Sleep(80); 
				return;	
			}
			gotoxy(mappingxy(ty),tx),printf("%s",no);
			Sleep(80);
		}
	}
}

int main(){
	srand((unsigned)time(NULL));
	int n,m;
	cin >> n;
	m = (n/2)*(n/2);
	init(n);
	system("cls"); 
	m--,book[1][1] = 1,map[1][1] = 0,map[1][0] =0;
	show(n);
	dfs(1,1,&m,n);
	system("cls");
	map[n-2][n-1] =0;
	show(n);
	gotoxy(0,1),printf("%s",nextturn[0]);
	find(1,0);
	getchar();
	getchar();
	getchar(); 
	return 0;
} 
