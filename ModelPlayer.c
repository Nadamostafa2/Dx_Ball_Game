

#include "ModelPlayer.h"
#include "Nokia5110.h"
#include "..//tm4c123gh6pm.h"
#include "TExaS.h"
#include "time.h"   // time()
#include "stdlib.h" // rand(), srand()

void ball_init (){
	int i,j;
	d=1;
	x=10,y=9;
}
void initlevel(){
	score=0;
	lifes=3;
	level=1;
}


void moveBall (){
	
//@TO DO complete directions and check if valid state before move 
int z;
if(d==0){
//	up lefttt y-- x--
z=ball_State(y-1,x-1);
changeStates(z);
if(z==0){
y--;
x--;
}
}
if(d==1){

// up y--
z=ball_State(y-1,x);
changeStates(z);
if(z==0){
y--;
}
}
if(d==2){

// up rightt y-- x++
z=ball_State(y-1,x+1);
changeStates(z);
if(z==0){
y--;
x++;
}
}
if(d==3){

// down lefttt y++ x--
z=ball_State(y+1,x-1);
changeStates(z);
if(z==0){
y++;
x--;
}
}
if(d==4){

// down  y++
z=ball_State(y+1,x);
changeStates(z);
if(z==0){
y++;
}
}
if(d==5){

// down rightt y++ x++
z=ball_State(y+1,x+1);
changeStates(z);
if(z==0){
y++;
x++;
}
}

}

	int ball_State(int y,int x){
if(y>=screenH)                   // the ball missed the ball --> lose
return -1;
if(y<=0)                        //hits upper border of screen
return 4;
if(x>=screenW || x<0 )            //the next state is out of borders 
return 3; 
if(screen[y][x]==0)           // the next state is an empty cell
return 0;
if(screen[y][x]==1)           // the state is that your next cell is ocubed by block
{screen[y][x]=0; EditScore();
return 1;}
if(screen[y][x]==2)            //when the next state is the slider 
return 2;
  return -1;                      //the error case when none of the above

}
	
void changeStates(int state){
		
			if(state==-1){
			lifes--;
			}
			if(state==1 ||state==2 ||state==3 ||state==4){
				 ChangeDiraction(state);	
				 ball_deleteCell();
		}	
	}


void ChangeDiraction(unsigned int state ){
if(state==1){ // if hits block move oppiste direction
if(d<=2)
	d=rand()%3+3; //move down
else
	d=rand()%3; // move up
}
if(state==2) // if hits slider move up
	d=rand()%3;

if(state==4)  //if hits the upper wall it will direct down 
	d=rand()%3+3;

if(state==3){ //if hits wall move in same direction
if(d>2)
	d=rand()%3+3; //move down
else
	d=rand()%3; 
}

}



	void EditScore(){
		score+=10*level;
	}


	
	void ball_deleteCell(){
		if( ball_State(y ,x-1)==1)   //check if u....
		{screen[y][x-1]=0;
			EditScore();}
		if( ball_State(y ,x+1)==1)   //check if u....
		{screen[y][x+1]=0;
			EditScore();}
		if( ball_State(y+1 ,x)==1)   //check if u....
		{screen[y+1][x]=0;
			EditScore();}
		if( ball_State(y-1,x)==1)   //check if u....
		{screen[y-1][x]=0;
			EditScore();}		
}
	

void setX(int ox){
x=ox;
}

void setY(int oy){
y=oy;
}

void setD(int dir){
d=dir;
}
void setScore(int S){
score=S;
}
void setLifes(int L){
lifes=L;
}
void setLevel(int L){
	level=L;
}

//getter

int GetX(){
return x;
}

int GetY(){
return y;
}

int GetD(){
return d;
}

int GetScore(){
return score;
}

int GetLifes(){
return lifes;
}

int GetLevel(){
	return level;
}

int GetScreen(int i,int j){
	return screen[i][j];
}
void setScreen(int i,int j,int state){
	screen[i][j]=state;
}