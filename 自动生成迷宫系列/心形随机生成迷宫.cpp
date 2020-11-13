/* 代码来源于：https://github.com/liuyubobobo/heart-curve-cplusplus/blob/master/main2.cpp */
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <windows.h>
const int height = 67;
const int width = 97;

// The first heart shape in hollow
// (x^2+y^2-1)^3 - x^2*y^3 = 0
// y ~ (-1.1 , 1.3 )
// x ~ (-1.2 , 1.2 )
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

int check(int i,int j){
	for(int a = 0; a < 4; a++){
		int ti = i + nextgo[a][0];
		int tj = j + nextgo[a][1];
		if(ti >= 0 && tj >= 0 && ti < height && tj < width){
			if(map[ti][tj]==0){
				return 1;
			}
		}
	}
	return 0;
}

void show(int n){
	for(int i = 0; i < height; i++){
		for(int j = 0; j < width; j++){
			if(map[i][j] == 1 && check(i,j)){
				printf("%s",wall);	
				book[i][j] = 2;	//边界		
			}else if(map[i][j] == 1){
				printf("%s",wall);	
				book[i][j] = 0;	
			}
			else printf("%s",air),book[i][j] = 0;
		}
		printf("\n");
	}	
}
void makelove(){
	int i = 0,j = 0;
    for( float y = 1.3; y >= -1.1 ; y -= 0.035 )
	{
		j = 0;
        for( float x = -1.2; x <= 1.2 ; x += 0.025 )
		{
            if( pow((x*x+y*y-1.0),3) - x*x*y*y*y >= 0.0 )
                printf("");
            else{
            	map[i][j] = 1;
            	 	//printf("口");
			}     
            j++;
		}
        //printf("\n");
        i++;
    }
 	//printf("%d,%d",i,j); 
} 
void init(int n){
	startx = 11,starty = width/2,endx = height-4,endy = width/2;
	getend= 0;
	makelove();
	/*for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			map[i][j] = 1;
		}
	}*/
}

void dfs(int x,int y,int *left,int n){
	if(*left == 0){
		return;
	}
	int randnum = rand() % 24;
	for(int i = 0; i < 4; i++){
		int tx = x + nextgo[randturn[randnum][i]][0];
		int ty = y + nextgo[randturn[randnum][i]][1];
		if(book[tx][ty] == 0 && tx > 0 && tx < height && ty > 0 && ty < width){
			map[x + (tx-x)/2][y+(ty-y)/2] = 0,gotoxy(mappingxy(y+(ty-y)/2),x + (tx-x)/2),printf("%s",air);
			Sleep(2);
			book[x + (tx-x)/2][y+(ty-y)/2] = 1;
			map[tx][ty] = 0,gotoxy(mappingxy(ty),tx),printf("%s",air);
			Sleep(2);
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
		if(book[tx][ty]==1){
			gotoxy(mappingxy(ty),tx),printf("\033[40;33m%s\033[0m",nextturn[i]);
			Sleep(5);
			book[tx][ty] = 0;
			find(tx,ty);
			if(getend){
				//system("color 27"); 
				gotoxy(mappingxy(ty),tx),printf("\033[42;32m%s\033[0m",yes);
				Sleep(5); 
				return;	
			}
			gotoxy(mappingxy(ty),tx),printf("\033[41;31m%s\033[0m",no);
			Sleep(5);
		}
	}
}

int main(){
	srand((unsigned)time(NULL));
	int n,m;
	n = height;
	m = (n/2)*(n/2);
	init(n);
	printf("多次按下回车开始"); 
	getchar();
	getchar();
	system("cls"); 
	show(n);
	dfs(startx,starty,&m,n);
	//system("cls");
	map[n-2][n-1] =0;
	//show(n);
	book[endx][endy] = 1;
	book[endx+1][endy] = 1;
	gotoxy(mappingxy(endy),endx),printf("%s",air);
	gotoxy(mappingxy(endy),endx+1),printf("%s",air);
	gotoxy(mappingxy(endy),endx+2),printf("%s",air);
	gotoxy(mappingxy(starty),startx-2),printf("%s",air);
	gotoxy(mappingxy(starty),startx-1),printf("%s",air);
	book[startx-1][starty] = 1;
	book[startx-2][starty] = 1;
	book[startx-3][starty] = 1;
	find(startx-3,starty);
	getchar();
	getchar();
	getchar(); 
	return 0;
} 

