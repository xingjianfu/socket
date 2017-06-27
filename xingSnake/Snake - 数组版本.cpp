#include <iostream>  
#include <ctime>
#include <cstdlib>  

#include "Map.h"
#include "Global.h"
#include "Snake.h"

using std::cout;
using std::endl;

Snake::Snake()
    : m_length(3)
	, m_foodCoordX(0)
	, m_foodCoordY(0) 
{
    m_belongMap = new Map(25,25);
	if (NULL == m_belongMap) {
		cout << "new m_belongMap error" << endl;
	}
		
	init();
	drawSnake();
	randomFood();		
}

Snake::Snake(int snakeLen, int mapWidth, int mapHeight)
	: m_length(snakeLen)
	, m_foodCoordX(0)
	, m_foodCoordY(0) 
{
	m_belongMap = new Map(mapWidth, mapHeight);
	    if (NULL == m_belongMap) {
		    cout << "new m_belongMap error" << endl;
	    }
	    
	init(); 
    drawSnake();
	randomFood();  
}

Snake::~Snake()
{
	if (NULL != m_belongMap) {
	    delete m_belongMap;
		m_belongMap = NULL;
	}
}

void Snake::init(void)
{
	//蛇出现在地图最中央  
	m_x[0] = m_belongMap->getWidth() / 2 + m_belongMap->getMapStartingCoordX();  
    m_y[0] = m_belongMap->getHeight() / 2 + m_belongMap->getMapStartingCoordY();  
        
    for (int i = 1; i < m_length; i++) {  
        m_x[i] = m_x[0];  //横身横坐标等于蛇头坐标 
        m_y[i] = m_y[i - 1] - 1; //蛇身纵坐标为上一节减1 
    } 	
}
//画蛇 
void Snake::drawSnake()
{  
    Display::setColor(10);  
    for (int i = 0; i < m_length; i++) {  
        Display::gotoXY(m_x[i], m_y[i]);  
        cout << "★" << endl;  
    }  
}

//随机产生食物
void Snake::randomFood()           
{
	srand((unsigned)time(NULL));
	do {
		//食物不能产生在四壁 
        m_foodCoordX = rand() % (m_belongMap->getWidth() - 2) + 1 + m_belongMap->getMapStartingCoordX(); 
        m_foodCoordY = rand() % (m_belongMap->getHeight() - 2) + 1 + m_belongMap->getMapStartingCoordY();
        
        //食物不能产生在蛇的身体上 
       	bool part = isPartOfBody();  
        if (false == part) {
			break;
		}
	} while(1);
	  
    Display::gotoXY(m_foodCoordX, m_foodCoordY);
	Display::setColor(12);
	cout << "●" << endl;	
}

//判断产生的食物是否在蛇的身体上 
bool Snake::isPartOfBody(void)       
{
	bool part = false;
	
	for (int i = 0; i < m_length; i++) {     
        if (m_foodCoordX == m_x[i] && m_foodCoordY == m_y[i]) { 
        	part = true;
			break;
	    } 
    }
	return part;
}

void Snake::snakeMove(char dir) 
{
	//蛇尾巴填充方框
	Display::gotoXY(m_x[m_length - 1], m_y[m_length - 1]);  
    Display::setColor(19);  
    cout << "■"; 
 
	//蛇的移动算法, 将前一节的坐标赋给后一节
    for (int i = m_length - 1; i > 0; i--) {  
        m_x[i] = m_x[i - 1];   
        m_y[i] = m_y[i - 1];  
    }
    
    //根据方向移动蛇的坐标 
	switch (dir) {
	case UP:
	  {
		m_y[0] = m_y[0] - 1;//蛇头纵坐标减1
	  }  
	  break;
	case DOWN:
	  {
		m_y[0] = m_y[0] + 1;//蛇头纵坐标加1
	  }  
	  break;
	case LEFT:
	  {
		m_x[0] = m_x[0] - 1;//蛇头横坐标减1
	  }  
	  break;
	case RIGHT:
	  {
		m_x[0] = m_x[0] + 1;//蛇头横坐标加1
	  }  
	  break;
	default:
      {
	  }
	  break; 
	}
}

//向上移动   
void Snake::moveUp()  
{
    snakeMove(UP);   
    drawSnake();  
}  

//向下移动  
void Snake::moveDown()  
{  
    snakeMove(DOWN); 
    drawSnake();  
}  

//向左移动  
void Snake::moveLeft()  
{
    snakeMove(LEFT); 
    drawSnake();  
}  

//向右移动  
void Snake::moveRight()  
{  
    snakeMove(RIGHT); 
    drawSnake();  
}

//判断是否吃到食物
bool Snake::eatFood()  
{  
    if ((m_x[0] == m_foodCoordX) && (m_y[0] == m_foodCoordY)) {    
        m_x[m_length] = m_x[m_length-1];//让新增加的蛇屁股坐标等于进食前的蛇屁股，移动后会自动刷新 
		m_y[m_length] = m_y[m_length-1];
		
		m_length += 1;
		
        randomFood();  //吃完之后产生食物
		 
        return true;  
    } 
	 
    return false;  
}   

//判断蛇是否碰到边框或者自己 
bool Snake::getLifeStatus(void) 
{
  	//判断是否碰到地图边框 
	bool lifeStatus = true;
	bool collisionStatus = false; 
	
    collisionStatus = isCollisionMapBorder();
    if (collisionStatus) {
    	lifeStatus = false;
    	return lifeStatus;
	}
	
	collisionStatus = isCollisionPartOfBody();
    if (collisionStatus) {
    	lifeStatus = false;
	}
	
    return lifeStatus;	  
}  

bool Snake::isCollisionMapBorder(void) 
{
	bool collisionStatus = false; 
	
    if ((m_x[0] <= m_belongMap->getMapStartingCoordX())       
        || (m_x[0] >= m_belongMap->getWidth() + m_belongMap->getMapStartingCoordX() - 1) 
        || (m_y[0] <= m_belongMap->getMapStartingCoordY()) 
        || (m_y[0] >= m_belongMap->getHeight() + m_belongMap->getMapStartingCoordY() - 1)) {
            
			collisionStatus = true;
		} 
		
	return collisionStatus;
}

bool Snake::isCollisionPartOfBody(void) 
{
	bool collisionStatus =false; 
          
    //判断是否碰到自己,从第4节开始算,因为头肯定碰不到第2/3节
    for (int i = 3; i < m_length; i++) {       
        if (m_x[0] == m_x[i] && m_y[0] == m_y[i]) {
        	collisionStatus = true;	
        	break;
		}           
    }
		
	return collisionStatus;
}



/*
//判断蛇是否碰到边框或者自己 
bool Snake::getLifeStatus(void) {
	
  	//判断是否碰到地图边框 
	int lifeStatus = true; 
    if (m_x[0] <= m_belongMap->getMapStartingCoordX()         
        || m_x[0] >= m_belongMap->getWidth() + m_belongMap->getMapStartingCoordX() - 1  
        || m_y[0] <= m_belongMap->getMapStartingCoordY()  
        || m_y[0] >= m_belongMap->getHeight() + m_belongMap->getMapStartingCoordY() - 1) {
            
			lifeStatus = false;
			 
			return lifeStatus;
		} 
    
	//判断是否碰到自己,从第4节开始算,因为头肯定碰不到第2/3节      
    int i = 0;
    for (i = 3; i < m_length; i++) {       
        if (m_x[0] == m_x[i] && m_y[0] == m_y[i]) {
        	lifeStatus = false;	
        	break;
		}           
    }
    return lifeStatus;	  
} 
*/ 
