/*****************************************************************************
**                                                                          **
**                          Snake Game by rcbgalido                         **
**                                                                          **
******************************************************************************
*****************************************************************************/

#include <stdio.h>
#include <conio.h>
#include <dos.h>
#include <stdlib.h>

void initializeGame();
void setFoodLocation();
void showFood();
void showInformation();
void showSnakePosition();
void changeSnakePosition();
void foodHit();
void snakeHit();
void moveLeft();
void moveRight();
void moveUp();
void moveDown();
void clearScreen(); //similar to clrscr() but it doesn't clear information (from showInformation()); minimizes blinking effect
void clearLine(int y);

int snakeX[200];
int snakeY[200];
int snakePrevX[200];
int snakePrevY[200];
int foodX, foodY;
int size, score;

void main(){
	char direction;
	initializeGame();
	while(1){
		if(kbhit()){
			direction=getch();
			if(direction==0x4b){
				moveLeft();
			}else if(direction==0x4d){
				moveRight();
			}else if(direction==0x48){
				moveUp();
			}else if(direction==0x50){
				moveDown();
			}else if(direction==27){
				break;
			}
		}
	}
	exit(0);
}

void initializeGame(){
	int x=0, y=0, z=36;
	while(x<=10){
		snakeX[x]=z;
		x++; 
		z++;
	}
	while(y<=10){
		snakeY[y]=14;
		y++;
	}
	
	size=10;
	score=0;

	clrscr();
	setFoodLocation();
	showFood();
	showSnakePosition();
	showInformation();
}

void setFoodLocation(){
	foodX=1+rand()%80; //1 to 80
	foodY=4+rand()%20; //4 to 23
}

void showFood(){
	gotoxy(foodX,foodY);
	printf("X");
}

void showInformation(){
	gotoxy(1,1);
	printf("================================================================================");
	gotoxy(1,2);
	printf("Snake Game by rcbgalido");
	gotoxy(1,3);
	printf("================================================================================");
	gotoxy(1,24);
	printf("================================================================================");
	gotoxy(58,25);
	printf("SIZE: %d  SCORE: %d",size,score);
	gotoxy(1,2);
}

void showSnakePosition(){
	int a=0;
	while(a<=size){
		gotoxy(snakeX[a],snakeY[a]);
		if(a==0){
			printf("%c",233); //head
		}else{
			printf("%c",254); //tail
		}
		a++;
	}
}

void changeSnakePosition(){
	int a=1;
	while(a<=size){
		snakePrevX[a]=snakeX[a];
		snakePrevY[a]=snakeY[a];
		snakeX[a]=snakePrevX[a-1];
		snakeY[a]=snakePrevY[a-1];
		a++;
	}
}

void foodHit(){
	if(snakeX[9]==foodX&&snakeY[9]==foodY){
		setFoodLocation();
		snakeX[size+1]=snakeX[size];
		snakeY[size+1]=snakeY[size];
		size++;
		score+=5;
	}
	
}

void snakeHit(){
	int a=0;
	char choice;
	while(a<size){
		if(snakeX[size]==snakeX[a]&&snakeY[size]==snakeY[a]){
			while(1){
				showSnakePosition();
				showInformation();
				clearLine(25);
				gotoxy(58,25);
				printf("PLAY AGAIN <Y/N>?: ");
				scanf("%c",&choice);
				if(choice=='Y'||choice=='y'){
					break;
				}else if(choice=='N'||choice=='n'){
					exit(0);
				}
			}
			main();
		}
		a++;
	}
}

void moveLeft(){
	while(1){
		delay(80);
		clearScreen();
		showFood();
		snakePrevX[0]=snakeX[0];
		snakePrevY[0]=snakeY[0];
		snakeX[0]=snakeX[0]-1;
		if(snakeX[0]==0){
			snakeX[0]=80;
		}
		snakeHit();
		if(snakeX[0]!=snakeX[1]){
			foodHit();
			changeSnakePosition();
			showSnakePosition();
			showInformation();
		}else{
			snakeX[0]=snakeX[0]+1;
			moveRight();
		}
		if(kbhit()){
			break;
		}
	}
}

void moveRight(){
	while(1){
		delay(80);
		clearScreen();
		showFood();
		snakePrevX[0]=snakeX[0];
		snakePrevY[0]=snakeY[0];
		snakeX[0]=snakeX[0]+1;
		if(snakeX[0]==81){
			snakeX[0]=1;
		}
		snakeHit();
		if(snakeX[0]!=snakeX[1]){
			foodHit();
			changeSnakePosition();
			showSnakePosition();
			showInformation();
		}else{
			snakeX[0]=snakeX[0]-1;
			moveLeft();
		}
		if(kbhit()){
			break;
		}
	}
}

void moveUp(){
	while(1){
		delay(80);
		clearScreen();
		showFood();
		snakePrevX[0]=snakeX[0];
		snakePrevY[0]=snakeY[0];
		snakeY[0]=snakeY[0]-1;
		if(snakeY[0]==3){
			snakeY[0]=23;
		}
		snakeHit();
		if(snakeY[0]!=snakeY[1]){
			foodHit();
			changeSnakePosition();
			showSnakePosition();
			showInformation();
		}else{
			snakeY[0]=snakeY[0]+1;
			moveDown();
		}
		if(kbhit()){
			break;
		}
	}
}

void moveDown(){
	while(1){
		delay(80);
		clearScreen();
		showFood();
		snakePrevX[0]=snakeX[0];
		snakePrevY[0]=snakeY[0];
		snakeY[0]=snakeY[0]+1;
		if(snakeY[0]==24){
			snakeY[0]=4;
		}
		snakeHit();
		if(snakeY[0]!=snakeY[1]){
			foodHit();
			changeSnakePosition();
			showSnakePosition();
			showInformation();
		}else{
			snakeY[0]=snakeY[0]-1;
			moveUp();
		}
		if(kbhit()){
			break;
		}
	}
}

void clearScreen(){
	int y=4;
	while(y<=23){
		clearLine(y);
		y++;
	}
}

void clearLine(int y){
	gotoxy(1,y);
	printf("                                                                               "); //79 spaces
	if(y!=25){ //going to point (80,25) results to bad behavior
		printf(" "); //1 space
	}
}
