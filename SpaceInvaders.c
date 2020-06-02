#include "..//tm4c123gh6pm.h"
#include "Nokia5110.h"
#include "Random.h"
#include "TExaS.h"
#include "ModelPlayer.h"

void DisableInterrupts(void); // 
void EnableInterrupts(void);  
void Timer2_Init(unsigned long period);
void Delaaay(unsigned long count); 
void PortF_Init(void);
void disableTimer(void);
void enableTimer(void);
void Drawing();
void Init();
int isAlive();
void GameOver();
void Level(int);
unsigned long counterTimer;
unsigned long Semaphore;
unsigned int BunkerX;
unsigned int BunkerY;
unsigned long lefttt,rightt;  // input from PF4,PF0 
unsigned long life;
unsigned long shoot; //button to play
// *************** Images *************

const unsigned char Bunker0[] = {
 0x42, 0x4D, 0xB2, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x76, 0x00, 0x00, 0x00, 0x28, 0x00, 0x00, 0x00, 0x12, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x01, 0x00, 0x04, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x3C, 0x00, 0x00, 0x00, 0xC4, 0x0E, 0x00, 0x00, 0xC4, 0x0E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x80,
 0x00, 0x00, 0x00, 0x80, 0x80, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x80, 0x00, 0x00, 0x80, 0x80, 0x80, 0x00, 0xC0, 0xC0, 0xC0, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF,
 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0xAA, 0xAA, 0x00, 0x00, 0x00, 0x00, 0x00, 0xAA, 0xAA, 0x00,
 0x00, 0x00, 0xAA, 0xAA, 0xA0, 0x00, 0x00, 0x00, 0x0A, 0xAA, 0xAA, 0x00, 0x00, 0x00, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0x00, 0x00, 0x00, 0x0A, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA,
 0xAA, 0xAA, 0xA0, 0x00, 0x00, 0x00, 0x00, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0x00, 0x00, 0x00, 0x00, 0xFF};

const unsigned char Cell[] ={
 0x42, 0x4D, 0x86, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x76, 0x00, 0x00, 0x00, 0x28, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x01, 0x00, 0x04, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0xC4, 0x0E, 0x00, 0x00, 0xC4, 0x0E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x80,
 0x00, 0x00, 0x00, 0x80, 0x80, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x80, 0x00, 0x00, 0x80, 0x80, 0x80, 0x00, 0xC0, 0xC0, 0xC0, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF,
 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0xF0, 0x00, 0x00, 0x0F, 0xF0,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF,};




// ************************ image dimensions out of BMP**********
#define BUNKERW     ((unsigned char)Bunker0[18])
#define BUNKERH     ((unsigned char)Bunker0[22])
#define CellW       ((unsigned char)Cell[18])
#define CellH       ((unsigned char)Cell[22])


void Init(){ 
int i,j;
ball_init();
BunkerY=10;
BunkerX=8;
	
for(j=0;j<screenW;j++)
setScreen(BunkerY,j,0);
for(j=BunkerX;j<BunkerX+5;j++)
setScreen(BunkerY,j,2);

}
void Drawing(){  //Delete Cell and display the remmaining after each shoot / update ArrOfCells 0=shooted 1=still not	
	int i,j;
  Nokia5110_ClearBuffer();
		  Nokia5110_Clear();

	// fill the untouched cells 
	for(i=0;i<screenH;i++)
		for(j=0;j<screenW;j++){
			if(GetScreen(i,j)==1)
						Nokia5110_PrintBMP(4*j, i*4+(CellH - 1), Cell, 0);
		}	
		Nokia5110_PrintBMP(4*GetX(), GetY()*4+(CellH - 1), image, 0);
		Nokia5110_PrintBMP(4*BunkerX, BunkerY*4+(BUNKERH - 1), Bunker0, 0);		
	  Nokia5110_Clear();
    Nokia5110_DisplayBuffer();      // Drawing buffer
	}
   
	void start (){
		int i,j;
		Nokia5110_Clear();
		Nokia5110_SetCursor(1, 2);
		Nokia5110_OutString("Welcome to  ");	
		Nokia5110_SetCursor(1, 4);
		Nokia5110_OutString("  DX_Ball  ");
		Nokia5110_SetCursor(0, 0); // renders screen
		Delaaay(60);
	}
	
	void instruction (){
		int i,j;
		Nokia5110_Clear();
		Nokia5110_SetCursor(1, 2);
		Nokia5110_OutString("sw1-->left ");	
		Nokia5110_SetCursor(1, 4);
		Nokia5110_OutString("sw2-->right");
		Nokia5110_SetCursor(0, 0); // renders screen
		Delaaay(60);
	
	}
	
	void Level(int level){
		int i,j;
		Nokia5110_Clear();
		Nokia5110_SetCursor(1, 2);
		Nokia5110_OutString("  Level  ");	
		Nokia5110_SetCursor(1, 4);
		Nokia5110_OutUDec(level);
		Delaaay(50);
		Nokia5110_SetCursor(0, 0); // renders screen
		Init();
		for(i=0;i<3+GetLevel();i++)     //number of initial blocks row depends on level
		for(j=0;j<screenW;j++){
			setScreen(i,j,1);	
		}
		
	}
	
	void WinGanme(){
	Nokia5110_Clear();
  Nokia5110_SetCursor(1, 1);
  Nokia5110_OutString("YOU WIN");
  Nokia5110_SetCursor(1, 2);
  Nokia5110_OutString("WELL DONE,");
  Nokia5110_SetCursor(0, 0); // renders screen
	}		
	
	
	
	void GameOver(){
	Nokia5110_Clear();
  Nokia5110_SetCursor(1, 1);
  Nokia5110_OutString("GAME OVER");
  Nokia5110_SetCursor(1, 2);
  Nokia5110_OutString("  Score");
	Nokia5110_SetCursor(1, 4);
  Nokia5110_OutUDec(GetScore());
  Nokia5110_SetCursor(0, 0); // renders screen
	}
	int main(void){ 
  TExaS_Init(NoLCD_NoScope);
  Nokia5110_Init();
	PortF_Init();
	Timer2_Init(600000000/30); 
	initlevel();
	Init();
	Nokia5110_ClearBuffer();
	      // Drawing buffer	
	start();
  instruction();		
	Level(1);
	Drawing();
	life=GetLifes();
 
		
	while(GetLifes()>0){
		if(GetLevel()==1&&GetScore()==2520){    //level 1 completed
			Level(2);
		}
		if(GetLevel()==2&&GetScore()==7560){    //level 2 completed
			Level(3);
		}
		if(GetLevel()==3&&GetScore()==15120){    //level 3 completed
			WinGanme();
			disableTimer();
		}
	}
 	
	GameOver();
}


void Timer2_Init(unsigned long x){ 
  unsigned long volatile delay;
  SYSCTL_RCGCTIMER_R |= 0x04;   // 0) activate timer2
  delay = SYSCTL_RCGCTIMER_R;
  counterTimer = 0;
  Semaphore = 0;
  TIMER2_CTL_R = 0x00000000;    // 1) disable timer2A during setup
  TIMER2_CFG_R = 0x00000000;    // 2) configure for 32-bit mode
  TIMER2_TAMR_R = 0x00000002;   // 3) configure for periodic mode, default down-count settings
  TIMER2_TAILR_R = x-1;    // 4) reload value
  TIMER2_TAPR_R = 0;            // 5) bus clock resolution
  TIMER2_ICR_R = 0x00000001;    // 6) clear timer2A timeout flag
  TIMER2_IMR_R = 0x00000001;    // 7) arm timeout interrupt
  NVIC_PRI5_R = (NVIC_PRI5_R&0x00FFFFFF)|0x80000000; // 8) priority 4
// interrupts enabled in the main program after all devicees initialized
// vector number 39, interrupt number 23
  NVIC_EN0_R = 1<<23;           // 9) enable IRQ 23 in NVIC
  TIMER2_CTL_R = 0x00000001;    // 10) enable timer2A
}
void disableTimer(){
	  TIMER2_CTL_R = 0x00000000;    //  disable timer2A
}
void enableTimer(void){
		TIMER2_CTL_R = 0x00000001;    //  enable timer2A
}



void Timer2A_Handler(void){ 
	
	int i,j;
  TIMER2_ICR_R = 0x00000001;   // acknowledge timer2A timeout
  counterTimer++;
	
  moveBall(); 
if(GetLifes()>0){
		 if(GetLifes()!=life){
			 Init();
			 life=GetLifes();
			 Delaaay(20);
		 }
		 lefttt = GPIO_PORTF_DATA_R&0x10;       // read PF4 into SW1
     rightt = GPIO_PORTF_DATA_R&0x01;     // read PF0 into SW2
		if(!lefttt&&!rightt)                     //means both pressed
			GPIO_PORTF_DATA_R = 0x02;        // LED is blue	
		else if(!lefttt&&rightt){                  // means just SW1 is pressed ..move lefttt
				  GPIO_PORTF_DATA_R = 0x04;     // LED is red		    
				if(BunkerX>=1)   					//if i press lefttt and i already at border,stay border
				{
					setScreen(BunkerY,BunkerX+4,0);
					setScreen(BunkerY,BunkerX-1,2);
					BunkerX--;
					
			}
		}
	    else if(!rightt&&lefttt){             // means just SW2 is pressed ..move rightt
			    GPIO_PORTF_DATA_R = 0x06;     // LED is green
				if(BunkerX<=15) {					//if i press rightt and i already at border,stay border
       		setScreen(BunkerY,BunkerX,0);
					setScreen(BunkerY,BunkerX+5,2);  
					BunkerX++;
					
				}
			}
	    else                             //means both not pressed
			  	GPIO_PORTF_DATA_R = 0x00;   // LED is off       	
        
Drawing();  
}
		
  Semaphore = 1; // trigger
}
void Delaaay(unsigned long a){unsigned long volatile time;
	disableTimer();
  while(a>0){
    time = 27240;  
    while(time){
	  	time--;
    }
    a--;
  }
	enableTimer();
}
void PortF_Init(void){ volatile unsigned long delay;
  SYSCTL_RCGC2_R |= 0x00000020;     // 1) F clock
  delay = SYSCTL_RCGC2_R;           // delay   
  GPIO_PORTF_LOCK_R = 0x4C4F434B;   // 2) unlock PortF PF0  
  GPIO_PORTF_CR_R = 0x1F;           // allow changes to PF4-0       
  GPIO_PORTF_AMSEL_R = 0x00;        // 3) disable analog function
  GPIO_PORTF_PCTL_R = 0x00000000;   // 4) GPIO clear bit PCTL  
  GPIO_PORTF_DIR_R = 0x0E;          // 5) PF4,PF0 input, PF3,PF2,PF1 output   
  GPIO_PORTF_AFSEL_R = 0x00;        // 6) no alternate function
  GPIO_PORTF_PUR_R = 0x11;          // enable pullup resistors on PF4,PF0       
  GPIO_PORTF_DEN_R = 0x1F;          // 7) enable digital pins PF4-PF0        
}
