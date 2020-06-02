/*
	ball.o
	this file controls the ball movements and
	directions and score and 
	

*/
/***************the directions************************/
// TO DO :Samar correct the direction
//d=0>>Nourth - East 
//d=1>Nourth
//d=2>>Nourth-East
//d=3>>South-East
//d=4>>South
//d=5>>South-west
//default >> nourth west
/*****************************************************/
 
  static unsigned int x;      // x coordinate
  static unsigned int y;      // y coordinate
	static unsigned int d;      //direction
	static unsigned int score;  // score
	static unsigned int level;  //level
	static unsigned int o;      //setter&getter
	static const unsigned int screenW = 21;   // screen grid width
	static const unsigned int screenH = 12; // screen grid height 
	static int lifes=3;
	
	//screen grid which will store the state of the grid cell 
	// cell=0 --> empty cell
	// cell=1 --> ocuped with block
	// cell=2 --> ocuped with slider 
	static unsigned int screen [screenH] [screenW];  
	
	
	// the ball ball wich will move 
	static const unsigned char image[] ={
	 0x42, 0x4D, 0x86, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x76, 0x00, 0x00, 0x00, 0x28, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x01, 0x00, 0x04, 0x00, 0x00, 0x00,
	 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0xC4, 0x0E, 0x00, 0x00, 0xC4, 0x0E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x80,
	 0x00, 0x00, 0x00, 0x80, 0x80, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x80, 0x00, 0x00, 0x80, 0x80, 0x80, 0x00, 0xC0, 0xC0, 0xC0, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF,
	 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF,
	 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF,};
	
	//initiate the screen grid and ball position at the begining  
	void ball_init (); 
	
	//initiate level ,score and lifes	
	void initlevel();
	 
	// will move the ball in its direction
	void moveBall ();
	 
	// change the direction of the ball if it hits something  
	void ChangeDiraction(unsigned int);
	 
	// return the current direction of the ball 
	unsigned int getDiraction();
	 
	 // returns the score of the ball 
	unsigned int Pll8ayer_getScore();
	 
	 // increment the score of the ball 
	void EditScore();
	 
		//check if the next step is valid or not 
	  //it returns one of the 3 states 
	  // 1- when the ball hits the wall 
	  // 2- when the ball hits cell block
	  // 3- when the ball hits the slider 
		// -1 which is error none of the obove "only for debuging it shouldnt be returned in the game".
	int ball_State(int,int);
	
	//delete blocks surrounded with the ball 
	//when the ball hits block this function called 
	//it will delete all touched blocks from 4 directions if found .
	
   void ball_deleteCell();
   void changeStates(int state);
	
	 //setter&&getter
	 void setX(int x);
   void setY(int y);
   void setD(int d);
   void setScore(int S);
   void setLifes(int L);
	 void setScreen(int,int,int);
	 void setLevel(int L);
   int GetX();
   int GetY();
   int GetD();
   int GetScore();
   int GetLifes();
	 int GetScreen(int,int);
	 int GetLevel();