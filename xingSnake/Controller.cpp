#include <conio.h>    
#include <iostream>
#include <windows.h> 

#include "Controller.h"
#include "Snake.h"
#include "Global.h"
   
Controller::Controller()
    : m_level(2)
	, m_score(0)
	, m_dir(DOWN)
{
	m_psnake = new Snake(3, 25, 25);  
    if (NULL == m_psnake) {
        std::cout <<"new snake error" << std::endl;
	}
}

Controller::Controller(int mapWidth, int mapHeight, int snakeLen, int level) 
	: m_level(level)
	, m_score(0)
	, m_dir(DOWN)
{
	m_psnake = new Snake(snakeLen, mapWidth, mapHeight);  
        if (NULL == m_psnake) {
    	    std::cout <<"new snake error" << std::endl;
	    }
}  

Controller::~Controller()
{
	if (NULL != m_psnake) {
	    delete m_psnake;
		m_psnake = NULL;
	}  
}

void Controller::init()
{
	m_psnake->init();
}

void Controller::draw()
{
	m_psnake->drawSnake();
}

void Controller::generateFood()
{
	m_psnake->randomFood();
}

//Running game
int Controller::run()  
{  
	int gameStatus = AGAIN; 
	int lifeStatus = ALIVE;
	char key = '\0';
	
	showScore();
	 
    while (1) {
        if (ALIVE == lifeStatus) {
        	int kb = kbhit();
        	//Get key information
            if (0 != kb) {  
                Display::gotoXY(0,40); 
                key = getche();  
            } 
            else {
            	key = m_dir;//No key, default down
			}
			       
			controlSnake(key); //Control game state
			
			unsigned int suspendTime = setSuspendTime(m_level);//Set suspend time
            Sleep(suspendTime);
            
			bool eatStatus = m_psnake->eatFood(); //eat food 
            if (eatStatus) { 
                m_score += 10;  
                showScore();
				
			    if(500 == m_score) {
				    gameStatus = winGame();
				    break;
			    }
            }
            
            lifeStatus = m_psnake->getLifeStatus();	//get snake life status
        } 
		 
        else {  
            gameStatus = gameOver(); 
            break;  
        }  
    } 

	return gameStatus; 
}  

//Control game state  
void Controller::controlSnake(char operate) 
{
    switch (operate) {  
    case UP:
	    {
		    if (DOWN != m_dir ) {   //To determine whether to move in the opposite direction    
                m_psnake->moveUp();  
                m_dir = operate;  
            }   
            else {
                m_psnake->moveDown(); 	
		    }      	
	    }  
	    break;  
    case DOWN:  
        {
            if (UP != m_dir) {  
                m_psnake->moveDown();  
                m_dir = operate;  
            }  
            else {
                m_psnake->moveUp(); 	
		    }            	
	    }
	    break; 
    case LEFT:  
        {
            if (RIGHT != m_dir) {  
                m_psnake->moveLeft();  
                m_dir = operate;  
            }  
            else {
                m_psnake->moveRight();
		    }  	
	    }
	    break;  
    case RIGHT:
	    {
		    if (LEFT != m_dir) {  
                m_psnake->moveRight();  
                m_dir = operate;  
            }  
            else {
                m_psnake->moveLeft();
		    } 	
	    }
	    break;              
	case PAUSE:  
        {
            pause();//pause	
	    }
	    break;  
    default:
        {
	    } 
	    break;       	
	}
}  

//Set suspend time
unsigned int Controller::setSuspendTime(int level)
{
	unsigned suspendTime = 0;
	
	switch (level) {
	case 1:
	    {
		    suspendTime = 300;	
	    }
	    break;
	case 2:
	    {
		    suspendTime = 200;	
	    }
	    break;
	case 3:
	    {
		    suspendTime = 100;	
	    }
	    break;
	case 4:
	    {
		    suspendTime = 50;
	    }
	    break;
	default:
        {
	    }
	    break; 
	}
	
	return suspendTime;
}

//pause
//Press the spacebar to pause, and then click continue
void Controller::pause(void)   
{  
    while (1) {
	    int kb = kbhit(); 
        if (0 != kb) {  
            Display::gotoXY(0, 40);  
            char p = getche();
			
		    if (PAUSE == p) {
			    break; 	
		    }	  
        }  
        	     
    }  
}  

//win game
//Enter 5 to continue, any other key to exit 
int Controller::winGame() 
{		
	system("cls"); 
	Display::setColor(12);
	std::cout << "\n\n\n\n===¡ô¡ó¡ô¡ó¡ô¡ó¡ô";
	Display::setColor(14);
	std::cout << "  Y O U   W I N  ";
	Display::setColor(12);
	std::cout << "¡ô¡ó¡ô¡ó¡ô¡ó¡ô====\n\n" << std::endl;
	Display::setColor(14);
    std::cout << "\t\tYou Got "<< m_score << " Scores" << std::endl;
	Display::setColor(12);
	std::cout << "\n\n\n  ===";
	Display::setColor(14);
	std::cout << " Do you want to continue the game? ";
	Display::setColor(12);
	std::cout << "  ===" << std::endl;
	std::cout << "\n\n\n  ===";
	Display::setColor(14);
	std::cout << " Enter 5 to continue, any other key to exit ";
	Display::setColor(12);
	std::cout << "  ===" << std::endl;
	
	int again;
	std::cin >> again;
	system("cls");
	
	return again; 	
}

//gameOver
// Enter 5 to continue, any other key to exit 
int Controller::gameOver(void) 
{	
	system("cls"); 
	Display::setColor(12);
	std::cout << "\n\n\n\n===¡ô¡ó¡ô¡ó¡ô¡ó¡ô";
	Display::setColor(14);
	std::cout << "  G A M E   O V E R  ";
	Display::setColor(12);
	std::cout << "¡ô¡ó¡ô¡ó¡ô¡ó¡ô====\n\n" << std::endl;
	Display::setColor(14);
	std::cout << "\t\tYou Got " << m_score << " Scores" << std::endl;;
	Display::setColor(12);
	std::cout << "\n\n\n  ===";
	Display::setColor(14);
	std::cout << " Do you want to continue the game? ";
	Display::setColor(12);
	std::cout << "  ===" << std::endl;
	std::cout << "\n\n\n  ===";
	Display::setColor(14);
	std::cout << " Enter 5 to continue, any other key to exit ";
	Display::setColor(12);
	std::cout << "  ===" << std::endl;
	
	int again;
	std::cin >> again;
	system("cls");
	
	return again; 
	
}

//show score
//Shown in the upper left corner
void Controller::showScore()  
{  
    Display::gotoXY(4, 1);  
    Display::setColor(14);  
    std::cout << m_score;  
}


















/*
if (NULL == m_psnake) {
	    	
	    cout << "m_snake is NULL" << endl;
	    return -1;
	}
*/
