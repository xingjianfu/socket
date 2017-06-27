#include <iostream>
#include <windows.h>

#include "Global.h"
#include "Map.h"

Map::Map()
    : m_mapWidth(25)
	, m_mapHeight(25)
	, m_mapStartCoordX(0)
	, m_mapStartCoordY(4)  
{
	drawMap();
}

Map::Map(int mapWidth, int mapHeight)
    : m_mapWidth(mapWidth)
	, m_mapHeight(mapHeight)
	, m_mapStartCoordX(0)
	, m_mapStartCoordY(4)  
{ 
	drawMap();    
} 

Map::~Map()
{	
}

//draw map
void Map::drawMap(void) 
{   
    Display::gotoXY(m_mapStartCoordX, m_mapStartCoordY);  
    Display::setColor(19);
    
    //draw map upper boundary
    int i = 0;
    for (i = 1; i<= m_mapWidth; i++) {
    	std::cout << "¡ö";
	}
	std::cout << std::endl;
	
	//draw map left and right boundary
	for (i = 1; i <= m_mapHeight-2; i++) {
		std::cout << "¡ö";
		Display::gotoXY(m_mapStartCoordX + m_mapWidth - 1, m_mapStartCoordY + i);
		std::cout << "¡ö";
		std::cout << std::endl;
	}
	
	//draw map Lower boundary
	for (i = 1; i<= m_mapWidth; i++) {
    	std::cout << "¡ö";
	} 	
}

int Map::getWidth(void)const 
{ 
    return m_mapWidth; 
}

int Map::getHeight(void)const 
{ 
    return m_mapHeight; 
}

int Map::getMapStartingCoordX(void)const 
{
    return m_mapStartCoordX; 
}

int Map::getMapStartingCoordY(void)const 
{
    return m_mapStartCoordY; 
}
