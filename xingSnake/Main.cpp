#include <iostream>

#include "Controller.h"
#include "Global.h"

int main()  
{
	int ret = 0;
	
	Display::welcome(); //Welcome interface
	
	int mapWidth = Display::inputMapWidth();//Set map width  
	int mapHeight = Display::inputMapHeight();//Set map height 
	int snakeLen = Display::inputSnakeLength();//Set snake length
	int level = Display::setLevel();//Set game level 
	
    int gameStatus = AGAIN;      
	do {
        Display::initWindow(); //Game interface header information
		    
	    Controller *controller = new Controller(mapWidth, mapHeight, snakeLen, level);// new Controller
	    if (NULL == controller) {
	        std::cout << "new controller error" << std::endl;
			ret = -1;
			break;	   
		}
		
		controller->init();
		controller->draw();
		controller->generateFood();
	
	    gameStatus = controller->run(); //Running game
		
		if (NULL != controller) {
	        delete controller;
		    controller = NULL;
	    }   		   
	} while(AGAIN == gameStatus);
	
	return ret;	
}  


















/* 
        Map *map = new Map(width, height, p);
	    if (NULL == map) {
		    cout << "new map error" << endl;
		    ret = -1;
		    break;
	    }
	     
        Snake *snake = new Snake(map, len); //初始化并画出蛇和蛇所吃的食物 
        if (NULL == snake) {
    	    cout <<"new snake error" << endl;
    	    //if (NULL != map) {
	        delete map;
		    map = NULL;
	        //}  
    	    ret = -1;
    	    break;   
	    }
	    */

