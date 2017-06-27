#ifndef MAP_H
#define MAP_H

class Map  
{ 
public:                       
    Map(int mapWidth, int mapHeight);
	~Map(); 
	   
    int getWidth(void)const;//Get map width 
    int getHeight(void)const;//Get map height 
    int getMapStartingCoordX(void)const;//Get the initial map coordinates X 
	int getMapStartingCoordY(void)const;//Get the initial map coordinates Y 
     	 
private:   
	int m_mapStartCoordX; //the initial map coordinates X 
	int m_mapStartCoordY;//the initial map coordinates Y  
    int m_mapWidth;// map width 
    int m_mapHeight;//map height
    
	Map();
 	Map(const Map&);
	Map& operator = (const Map&);
	 
	void drawMap(void); //draw map 
};  

#endif /*MAP_H*/
/*EOF*/
