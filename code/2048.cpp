#include<stdio.h>
#include<windows.h> 
#include<stdlib.h>
#include<time.h>
#include<conio.h>
#include<math.h>
#include<string.h>
#include<direct.h>
#include<io.h>
#include<Easyx.h>
#include<mmsystem.h>
#include <iostream>
#pragma comment(lib,"winmm.lib")
int map[4][4];
int score = 0;
void init() {//init map data
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			map[i][j] = 0;//delegate that there is no number
	//generate random number
	srand(time(0));
	int x1 = rand() % 4;
	int y1 = rand() % 4;
	generate_origin_again: int x2 = rand() % 4;
	int y2 = rand() % 4;//randomly generate number at different two place
	if (x1 == x2)
		if (y1 == y2)
			goto generate_origin_again;
	map[x1][y1] = 2;
	map[x2][y2] = 2;//original number
	//sample
	int sample = 4096;
	for (int i = 0; i <= 2; i++) {
		if (i == 0 || i == 2)
			for (int j = 0; j < 4; j++) {
				map[i][j] = sample;
				sample = sample / 2;
			}
		else if (i == 1)
			for (int j = 3; j >= 0; j--) {
				map[i][j] = sample;
				sample = sample / 2;
			}
	}
	score = 047;
	//sample
	
	//test
	//map[0][0] = 2;
	//map[0][1] = 2;
	//map[0][2] = 4;
	//map[0][3] = 4;
	//test
}
void drawnumber(int number, int x, int y) {
	IMAGE number_picture;
	//load number picture
	if (number == 2)
		loadimage(&number_picture, "data/2.jpg");
	else if (number == 4)
		loadimage(&number_picture, "data/4.jpg");
	else if (number == 8)
		loadimage(&number_picture, "data/8.jpg");
	else if (number == 16)
		loadimage(&number_picture, "data/16.jpg");
	else if (number == 32)
		loadimage(&number_picture, "data/32.jpg");
	else if (number == 64)
		loadimage(&number_picture, "data/64.jpg");
	else if (number == 128)
		loadimage(&number_picture, "data/128.jpg");
	else if (number == 256)
		loadimage(&number_picture, "data/256.jpg");
	else if (number == 512)
		loadimage(&number_picture, "data/512.jpg");
	else if (number == 1024)
		loadimage(&number_picture, "data/1024.jpg");
	else if (number == 2048)
		loadimage(&number_picture, "data/2048.jpg");
	else if (number == 4096)
		loadimage(&number_picture, "data/4096.jpg");
	putimage(x, y, &number_picture);
}
void drawface(int map[][4]) {
	cleardevice();
	IMAGE background;
	loadimage(&background, "data/nightstar.jpg");
	putimage(0, 0, &background);
	settextcolor(RGB(102, 204, 255));
	setbkmode(TRANSPARENT);
	settextstyle(50, 0, "Old English Text MT");
	outtextxy(0, 0, "score:");
	char OUT_score[10];
	sprintf(OUT_score, "%d", score);
	outtextxy(130, 0, OUT_score);
	for(int i=0;i<4;i++)//This is x
		for (int j = 0; j < 4; j++) {//This is y
			//draw number
			if (map[i][j] > 0) {//There are number 
				drawnumber(map[i][j], i*100, j*100+50);
			}
		}
}
void Gameoriginalface() {
	initgraph(400, 450);//400°¡400 is game face and 400°¡50 is score's line
	mciSendString("open data/ÕÌ–«.mp3", 0, 0, 0);
	mciSendString("play data/ÕÌ–«.mp3 repeat", 0, 0, 0);
	//IMAGE background;
	//loadimage(&background, "data/nightstar.jpg");
	//putimage(0, 0, &background);
	//settextcolor(RGB(102,204,255));
	////settextstyle(50, 0, "Old English Text MT");
	//outtextxy(0, 0, "score:");
	init();
	drawface(map);
}
int generate_new() {//1 is keeping on,2 is gaming over
	//Keeping on
	srand(time(0));
	int existance = 0;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			if (map[i][j] == 0)
				existance = 1;//there is space
	int flag = 0;//0 is Gameover but 1 is Gamekeeping
	if (existance == 0) {//	there is no space
		for(int i=0;i<=2;i++)
			for (int j = 0; j <= 2; j++) {
				if ((map[i][j] == map[i + 1][j]) || (map[i][j] == map[i][j + 1])) {//beside line retrieval and beside row retrieval
					flag = 1;
				}
				if (j == 2) {//Don't check up and down
					if (map[i][j + 1] == map[i + 1][j + 1]) {
						flag = 1;
					}
				}
				if(i==2){//Don't check left and right
					if (map[i + 1][j] == map[i + 1][j + 1]) {
						flag = 1;
					}
				}
			}
		if (flag == 1)//Game keep on and unnecessaryly generate new number
			return 1;
		else if (flag == 0)//GameOver
			return 2;
	}
	generate_new_again:int x = rand() % 4;
	int y = rand() % 4;
	if (map[x][y] == 0) {
		map[x][y] = rand() % 10 ? 2 : 4;
		return 1;
	}
	else if(map[x][y] > 0)
		goto generate_new_again;
}
void move_animation(int currentX,int currentY, int endX, int endY) {//moving animation
	int memory = map[currentX][currentY];
	int memory_currentY = currentY;
	int memory_endY = endY;
	int memory_currentX = currentX;
	int memory_endX = endX;
	map[currentX][currentY] = 0;
	if(currentX==endX){//move up or down
		currentY = currentY * 100 + 50;
		endY = endY * 100 + 50;
		if (endY < currentY) {//move to up
			for (int j = currentY; j > endY; j -= ((currentY - endY) / 5)) {
				BeginBatchDraw();//Frames draw
					drawface(map);
					drawnumber(memory, currentX*100, j);
				EndBatchDraw();
			}
		}
		else if (endY > currentY) {//move to down
			for (int j = currentY; j < endY; j += ((endY - currentY) / 5)) {
				BeginBatchDraw();//Frames draw
					drawface(map);
					drawnumber(memory, currentX * 100, j);
				EndBatchDraw();
			}
		}
	}
	else if(currentY==endY){//move left or right
		currentX = currentX * 100;
		endX = endX * 100 ;
		if (endX < currentX) {//move to left
			for (int i = currentX; i > endX; i -= ((currentX - endX) / 5)) {
				BeginBatchDraw();//Frames draw
					drawface(map);
					drawnumber(memory, i, currentY * 100 + 50);
				EndBatchDraw();
			}
		}
		else if (endX > currentX) {//move to right
			for (int i = currentX; i < endX; i += ((endX - currentX) / 5)) {
				BeginBatchDraw();//Frames draw
					drawface(map);
					drawnumber(memory, i, currentY * 100 + 50);
				EndBatchDraw();
			}
		}
	}
	map[memory_currentX][memory_currentY] = memory;
}
//void generate_animation(int currentX, int currentY) {
//	IMAGE number1,number2,number3;
//	if (map[currentX][currentY] == 4) {
//		loadimage(&number1, "data/4_1.jpg");
//		loadimage(&number2, "data/4_2.jpg");
//		loadimage(&number3, "data/4_3.jpg");
//	}
//	putimage(currentX * 100, currentY * 100 + 50, &number1);
//	putimage(currentX * 100, currentY * 100 + 50, &number2);
//	putimage(currentX * 100, currentY * 100 + 50, &number3);
//}
void moveup() {
	mciSendString("close data/dong.mp3", 0, 0, 0);
	mciSendString("open data/dong.mp3", 0, 0, 0);
	mciSendString("play data/dong.mp3", 0, 0, 0);
	int flag1 = 0;
	int k=0,i=0,j=0;//k is retrieval current line
	int flag2[4] = {0,0,0,0};//repect current row
	//add same number 
	for (int i = 0; i <= 3; i++)//traverse each row
		for (int j = 0; j < 3; j++) {//traverse each line
			if ((map[i][j] == map[i][j + 1])&&(map[i][1]!=0)) {//two number is equal and a special situation
				map[i][j] = map[i][j] + map[i][j + 1];
				score += map[i][j];
				//generate_animation(i, j);
				map[i][j + 1] = 0;
				flag2[i] = map[i][j];
			}
		}
	//move all number to up
	for (i = 0; i < 4; i++) {//inspect each row
		//a line to a line from up to down,move the first number to up where can be got
		for (j = 0; j < 3; j++) {//inspect each line in current row
			k = j;//'j' delegate current line ,'k'delegate retrieval place
			flag1 = 0;//It become 1 when there is no number and 2 when there is number
			while (map[i][k] == 0) {//If there is no number retrieval the next place
				k++;
				flag1 = 1;//set there is no number
				if (k == 3)//touch down
					break;//stop retrivaling this row
			}
			if (flag1) {
				move_animation(i, k, i, j);
				map[i][j] = map[i][k];//move to up
				map[i][k] = 0;//the place it existed just now become 0
				if ((j > 0) && (flag2[i] !=map[i][j])) {//inspect whether here is up
					if (map[i][j] == map[i][j - 1]) {//add same number,the situation is two number is equal
						map[i][j - 1] = map[i][j] + map[i][j - 1];
						score += map[i][j - 1];
						//generate_animation(i, j-1);
						map[i][j] = 0;
						j--;//traverse this line again
						flag2[i] = map[i][j];
					}
				}
			}
		}
	}
}
void movedown() {
	mciSendString("close data/dong.mp3", 0, 0, 0);
	mciSendString("open data/dong.mp3", 0, 0, 0);
	mciSendString("play data/dong.mp3", 0, 0, 0);
	//move all number to down
	int flag1 = 0;
	int flag2[4]={0,0,0,0};
	int k = 0, i = 0, j = 0;//retrieval current line
	//add same number 
	for (int i = 3; i >= 0; i--) {//traverse each row
		for (int j = 3; j > 0; j--) {//traverse each line
			if ((map[i][j] == map[i][j - 1]) && (map[i][2] != 0)) {//two number is equal and a specical situation
				map[i][j] = map[i][j] + map[i][j - 1];
				score += map[i][j];
				//generate_animation(i, j);
				map[i][j - 1] = 0;
				flag2[i] = map[i][j];
			}
		}
	}
	for (i = 0; i < 4; i++) {//inspect each row
		//a line to a line from down to up,move the first number to up where can be got
		for (j = 3; j > 0; j--) {//inspect each line in current row
			k = j;//'j' delegate current line ,'k'delegate retrieval place
			flag1 = 0;//It become 1 when there is no number and 2 when there is number
			while (map[i][k] == 0) {//If there is no number retrieval the next place
				k--;
				flag1 = 1;//set there is no number
				if (k == 0)//touch up
					break;//stop retrivaling this row
			}
			if (flag1) {
				move_animation(i, k, i, j);
				map[i][j] = map[i][k];//move to down
				map[i][k] = 0;//the place it existed just now become 0
				if (j < 3 && (flag2[i]!=map[i][j])) {
					if (map[i][j] == map[i][j + 1]) {
						map[i][j + 1] = map[i][j] + map[i][j + 1];
						score += map[i][j + 1];
						//generate_animation(i, j+1);
						map[i][j] = 0;
						j++;
						flag2[i] = map[i][j];
					}
			}
		}
	}
}
void moveleft() {
	mciSendString("close data/dong.mp3", 0, 0, 0);
	mciSendString("open data/dong.mp3", 0, 0, 0);
	mciSendString("play data/dong.mp3", 0, 0, 0);
	//move all number to left
	int flag1 = 0;
	int k = 0, i = 0, j = 0;//k is retrieval current row
	int flag2[4] = {0,0,0,0};
	//add same number 
	for (int j = 0; j <= 3; j++)//traverse each line
		for (int i = 0; i < 3; i++) {//traverse each row
			if ((map[i][j] == map[i + 1][j])&&(map[1][j]!=0)) {//two number is equal and a special situation
				map[i][j] = map[i][j] + map[i + 1][j];
				score += map[i][j];
				//generate_animation(i, j);
				map[i + 1][j] = 0;
				flag2[j] = map[i][j];
			}
		}
	for (j = 0; j < 4; j++) {//inspect each line
		//a row to a row from left to right,move the first number to up where can be got
		for (i = 0; i < 3; i++) {//inspect each row in current line
			k = i;//'i' delegate current row ,'k'delegate retrieval place
			flag1 = 0;//It become 1 when there is no number and 2 when there is number
			while (map[k][j] == 0) {//If there is no number retrieval the next place
				k++;
				flag1 = 1;//set there is no number
				if (k == 3)//touch right
					break;//stop retrivaling this row
			}
			if (flag1) {
				move_animation(k, j, i, j);
				map[i][j] = map[k][j];//move to left
				map[k][j] = 0;//the place it existed just now become 0
				if (i > 0 && (flag2[j]!=map[i][j])) {
					if (map[i][j] == map[i - 1][j]) {
						map[i - 1][j] = map[i][j] + map[i - 1][j];
						score += map[i - 1][j];
						//generate_animation(i-1, j);
						map[i][j] = 0;
						i--;
						flag2[j] = map[i][j];
					}
				}
			}
		}
	}
}
void moveright() {
	mciSendString("close data/dong.mp3", 0, 0, 0);
	mciSendString("open data/dong.mp3", 0, 0, 0);
	mciSendString("play data/dong.mp3", 0, 0, 0);
	//move all number to right
	int flag1 = 0;
	int k = 0, i = 0, j = 0;//k is retrieval current row
	int flag2[4] = {0,0,0,0};
	//add same number 
	for (int j = 0; j <= 3; j++)//traverse each line
		for (int i = 3; i > 0; i--) {//traverse each row
			if ((map[i][j] == map[i - 1][j])&&(map[2][j]!=0)) {//two number is equal
				map[i][j] = map[i - 1][j] + map[i][j];
				score += map[i][j];
				//generate_animation(i, j);
				map[i - 1][j] = 0;
				flag2[j] = map[i][j];
			}
		}
	for (j = 0; j < 4; j++) {//inspect each line
		//a row to a row from right to left,move the first number to up where can be got
		for (i = 3; i > 0; i--) {//inspect each row in current line
			k = i;//'i' delegate current line ,'k'delegate retrieval place
			flag1 = 0;//It become 1 when there is no number and 2 when there is number
			while (map[k][j] == 0) {//If there is no number retrieval the next place
				k--;
				flag1 = 1;//set there is no number
				if (k == 0)//touch left
					break;//stop retrivaling this line
			}
			if (flag1) {
				move_animation(k, j, i, j);
				map[i][j] = map[k][j];//move to up
				map[k][j] = 0;//the place it existed just now become 0
				if (i < 3 && (flag2[j]!=map[i][j])) {
					if (map[i][j] == map[i + 1][j]) {
						map[i + 1][j] = map[i + 1][j] + map[i][j];
						score += map[i + 1][j];
						//generate_animation(i+1, j);
						map[i][j] = 0;
						i++;
						flag2[j] = map[i][j];
					}
				}
			}
		}
	}
}
int GameOver() {//return 1 is play again but return 2 is leaving
	settextcolor(RGB(53,53, 205));
	settextstyle(25, 0, "Old English Text MT");
	outtextxy(150, 160, "Game Over!!! ");
	outtextxy(100, 210, "hit y to play again ");
	outtextxy(30, 260, "and hit other key to leave");
	Sleep(2000);
	switch (getch()) {
		case 'y':
			score = 0;
			return 1;
		default:
			return 2;
	}
}
int main(int argc, const char* argv[]) {
replay_again:Gameoriginalface();//load game face
	while (1) {//Game logic
	again:
			switch (getch()) {
			case 'w'://move to up
				moveup();
				break;
			case 'a'://move to left
				moveleft();
				break;
			case 'd'://move to right
				moveright();
				break;
			case 's'://move to down
				movedown();
				break;
			default:
				goto again;
			}
			switch (generate_new()) {
			case 1://Keep on
				drawface(map);
				break;
			case 2://Game Over
				switch (GameOver()) {
				case 1://replay again
					goto replay_again;
					break;
				case 2://leave game
					return 1;
				}
				break;
			}
	}
	system("pause");
	return 0;
}
