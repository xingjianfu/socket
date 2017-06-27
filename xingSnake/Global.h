#ifndef GLOBAL_H  
#define GLOBAL_H 

const char PAUSE = 32;
const char UP = 72;
const char LEFT = 75;
const char RIGHT = 77;
const char DOWN = 80;

const char ALIVE = 1;

const char AGAIN = 5;

namespace Display
{
	void welcome(void);                        //Welcome interface
	int inputMapWidth(void);                  //Set map width
	int inputMapHeight(void);                 //Set map height 
	int inputSnakeLength(void);              //Set snake length
    int setLevel(void);                      //Set game level 
	void initWindow(void);                   //Game interface header information
    void gotoXY(int x, int y);               //Jump coordinates   
	void setColor(int colorId);	             //Set output color
}

#endif /*GLOBAL_H*/
/*EOF*/ 
