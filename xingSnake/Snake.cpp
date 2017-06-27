#include <iostream>  
#include <ctime>
#include <cstdlib>  

#include "Map.h"
#include "Global.h"
#include "Snake.h"

Snake::Snake()
    : m_length(3)
	, m_foodCoordX(0)
	, m_foodCoordY(0) 
{
    m_belongMap = new Map(25,25);
	if (NULL == m_belongMap) {
		std::cout << "new m_belongMap error" << std::endl;
	}
		
	//init();
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
		    std::cout << "new m_belongMap error" << std::endl;
	    }
	    
	//init(); 
    //drawSnake();
    
	//randomFood();  
}

Snake::~Snake()
{
	if (NULL != m_belongMap) {
	    delete m_belongMap;
		m_belongMap = NULL;
	}
}

//add snake Node
void Snake::addSnakeNode(int snakeX,int snakeY) 
{
	std::vector<int> snakeNode;
	snakeNode.push_back(snakeX);
	snakeNode.push_back(snakeY);
	m_snakeCoord.push_back(snakeNode);
}

void Snake::init(void)
{
	//The snake is in the center of the ma
	
	int snakeHeadX =  m_belongMap->getWidth() / 2 + m_belongMap->getMapStartingCoordX();
	int snakeHeadY =  m_belongMap->getHeight() / 2 + m_belongMap->getMapStartingCoordY();
     
	addSnakeNode(snakeHeadX, snakeHeadY); //add snake head coordinate
    
    
	for (int i = 1; i < m_length; i++) {
		//The snake body coordinate X is equal to the snake head coordinate X ,
		//The snake body coordinate Y is equal to the snake head Y minus i
		addSnakeNode(snakeHeadX,snakeHeadY - i);	 
    }
}
//draw snake
void Snake::drawSnake()
{  
    Display::setColor(10);  
    for (int i = 0; i < m_length; i++) {  
        Display::gotoXY(m_snakeCoord[i][0], m_snakeCoord[i][1]);  
        std::cout << "★" << std::endl;  
    }  
}

//Random food
void Snake::randomFood()           
{
	//foodProductRangeSize: Width and height minus 2
	int foodProductRangeSizeX = m_belongMap->getWidth() - 2;
	int foodProductRangeSizeY = m_belongMap->getHeight() - 2;
	
	srand((unsigned)time(NULL));
	do {
		//food cannot be produced at the edges of the map 
        m_foodCoordX = rand() % (foodProductRangeSizeX) + 1 + m_belongMap->getMapStartingCoordX(); 
        m_foodCoordY = rand() % (foodProductRangeSizeY) + 1 + m_belongMap->getMapStartingCoordY();
        
        //Food cannot be produced on the body of a snake 
       	bool part = isPartOfBody();  
        if (!part) {
			break;
		}
	} while(1);
	  
    Display::gotoXY(m_foodCoordX, m_foodCoordY);
	Display::setColor(12);
	std::cout << "●" << std::endl;	
}

//To determine whether the food produced on the snake's body 
bool Snake::isPartOfBody(void)       
{
	bool part = false;
	
	for (int i = 0; i < m_length; i++) {     
        if (m_foodCoordX == m_snakeCoord[i][0] && m_foodCoordY == m_snakeCoord[i][1]) { 
        	part = true;
			break;
	    } 
    }
	return part;
}

void Snake::snakeMove(char dir) 
{
	//Snake tail fill space
	Display::gotoXY(m_snakeCoord[m_length - 1][0], m_snakeCoord[m_length - 1][1]);   
    std::cout << " "; 
 
	//Snake mobile algorithm, the previous section of the coordinates assigned to the latter section
    for (int i = m_length - 1; i > 0; i--) {  
		m_snakeCoord.at(i) = m_snakeCoord.at(i-1);	    
    }
    
    //According to the direction of mobile snake head coordinates
	switch (dir) {
	case UP:
	    {
		    m_snakeCoord[0][1] = m_snakeCoord[0][1] -1;
	    }  
	    break;
	case DOWN:
	    {
		    m_snakeCoord[0][1] = m_snakeCoord[0][1] + 1;
	    }  
	    break;
	case LEFT:
	    {
		    m_snakeCoord[0][0] = m_snakeCoord[0][0] - 1;
	    }  
	    break;
	case RIGHT:
	    {
		    m_snakeCoord[0][0] = m_snakeCoord[0][0] + 1;
	    }  
	    break;
	default:
        {
	    }
	    break; 
	}
}

//Move up   
void Snake::moveUp()  
{
    snakeMove(UP);   
    drawSnake();  
}  

//Move DOWN  
void Snake::moveDown()  
{  
    snakeMove(DOWN); 
    drawSnake();  
}  

//Move LEFT  
void Snake::moveLeft()  
{
    snakeMove(LEFT); 
    drawSnake();  
}  

//Move RIGHT  
void Snake::moveRight()  
{  
    snakeMove(RIGHT); 
    drawSnake();  
}

//Determine whether to eat food
bool Snake::eatFood()  
{  
    if ((m_snakeCoord[0][0] == m_foodCoordX) 
	    && (m_snakeCoord[0][1] == m_foodCoordY)) {    
        //The new Snake  tail coordinates are equal to that of the snake before eating 
		m_snakeCoord.push_back(m_snakeCoord[m_length-1]);
		
		m_length += 1;	
        
		randomFood(); 
		 
        return true;  
    } 
	 
    return false;  
}   

//To determine whether the snake hit the map boundaries or their own 
bool Snake::getLifeStatus(void) 
{
  	
	bool lifeStatus = true;
	bool collisionStatus = false; 
	
	//To determine whether the collision to the map border
    collisionStatus = isCollisionMapBorder();
    if (collisionStatus) {
    	lifeStatus = false;
    	return lifeStatus;
	}
	
	//Judge whether or not to meet their own
	collisionStatus = isCollisionPartOfBody();
    if (collisionStatus) {
    	lifeStatus = false;
	}
	
    return lifeStatus;	  
}  

//To determine whether the collision to the map border
bool Snake::isCollisionMapBorder(void) 
{
	bool collisionStatus = false; 
	
	int mapLeftBorder = m_belongMap->getMapStartingCoordX();
	int mapRightBorder = m_belongMap->getWidth() + m_belongMap->getMapStartingCoordX() - 1;
	int mapUPBorder = m_belongMap->getMapStartingCoordY();
	int mapDownBorder = m_belongMap->getHeight() + m_belongMap->getMapStartingCoordY() - 1;
	
    if ((m_snakeCoord[0][0] <= mapLeftBorder)       
        || ( m_snakeCoord[0][0] >= mapRightBorder) 
        || ( m_snakeCoord[0][1] <= mapUPBorder) 
        || ( m_snakeCoord[0][1] >= mapDownBorder) ) {
            
			collisionStatus = true;
		} 
		
	return collisionStatus;
}


//To determine whether the collision to the map border
bool Snake::isCollisionPartOfBody(void) 
{
	bool collisionStatus =false; 
          
    /*Determine whether the collision to their own, 
	from the beginning of the fourth quarter, because the head collision less than section 2/3 */
    for (int i = 3; i < m_length; i++) {       
        if ( m_snakeCoord.at(0) == m_snakeCoord.at(i)) {
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
/*
//蛇出现在地图最中央
	//typedef vector<int> snakeNode;
	//typedef vector< snakeNode > snake;
	//typedef vector< vector<int> >::iterator
	//snake a;
	//vector< vector<int> >::iterator = m_snakeCoord.begin();
*/
	#if 0
	//vector< vector<int> >::iterator i = m_snakeCoord.begin();
	vector<int> snakeHead;
	snakeHead.push_back(snakeHeadX);
	snakeHead.push_back(snakeHeadY);
	m_snakeCoord.push_back(snakeHead);
	
	createNode(snakeHead, snakeHeadX, snakeHeadYs)
	createNode(vecotr<int> &v, x, y) {
		v.push_back(x);
		v.push_back(y);	
	}
	addNode( snakeHead)
	addNode(snakeNode &v) {
		m_snake.push+b(v);
	}
	#endif 
	
	/*
	//, m_snakeCoord(1, std::vector<int>(1, 1))
    //m_snakeCoord.pop_back();
	*/ 
