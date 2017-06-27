#ifndef CONTROLLER_H  
#define CONTROLLER_H 

class Snake;
  
class Controller  
{
public:   
    Controller(int mapWidth, int mapHeight, int snakeLen, int level);
	~Controller(void);
	 
    int run(void);   //Running game
    void init(void);
    void draw(void);
    void generateFood(void);
 	 	
private:  
    Snake* m_psnake;  //Controlled snake 
	char m_dir;     //direction 
    int m_level; //game level
    int m_score; //game score 
	
	Controller(); 
	Controller(const Controller&);
	Controller & operator = (const Controller&);
	
	void controlSnake(char oper);   //Control game state
	unsigned int setSuspendTime(int level); //Set suspend time 
    void pause(void);              //Pause game 
    int winGame(void);             //Win game 
	int gameOver(void);            //gameOver  
	void showScore(void);           //showScore 
};  
  
#endif /*CONTROLLER_H */
/*EOF*/  
