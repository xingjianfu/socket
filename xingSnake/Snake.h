#ifndef SNAKE_H  
#define SNAKE_H 

#include <vector>

class Map;

class Snake  
{
public:  
    Snake(int snakeLen, int mapWidth, int mapHeight);
	~Snake();
    
    void init();//Initialization 
	void drawSnake(void);//draw snake 
	void randomFood(void);//Random food
	bool eatFood(void);//eat food 
	
    void moveUp(void);//move UP 
    void moveDown(void);//move DOWN  
    void moveLeft(void);//move LEFT  
    void moveRight(void);//move RIGH
	  
    bool getLifeStatus(void);//get life status  
    
private:  
	std::vector< std::vector<int> > m_snakeCoord; //snake position coordinate
    Map* m_belongMap;//snake map 
    int m_length; //snake length  
	int m_foodCoordX;//Food coordinate X  
	int m_foodCoordY;// Food coordinate Y 
	
	Snake();
 	Snake(const Snake&);
	Snake & operator = (const Snake&);
	
	
	void addSnakeNode(int snakeX,int snakeY);//add Snake Node

	bool isPartOfBody();//Is it part of the snake body
	 
	void snakeMove(char dir);//Snake Movement
	
	bool isCollisionMapBorder();//Collision to map boundary 
	bool isCollisionPartOfBody(); //Collision to snake body 
}; 

#endif /*SNAKE_H*/
/*EOF*/ 
