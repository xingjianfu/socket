#include <iostream>
#include <windows.h>

#include "Global.h"

namespace Display 
{
    //Welcome interface
	void welcome(void)                                           
	{
		std::cout <<"                                                                                " << std::endl;
		setColor(13);
		std::cout <<" ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ " << std::endl;
		setColor(14);
		std::cout <<"  ■■■■■    ■■■        ■■      ■■■      ■■       ■  ■■■■■■ ";
		std::cout <<"■■■■■■■  ■■■■      ■■    ■■■■■    ■■      ■   ■■■■■■ ";
		std::cout <<"■■■  ■■■  ■■ ■■     ■■   ■■    ■■   ■■    ■     ■■         ";
		std::cout <<"■■■          ■■  ■■    ■■  ■■      ■■  ■■  ■       ■■         ";
		std::cout <<"  ■■■■      ■■   ■■   ■■  ■■      ■■  ■■ ■        ■■■■■■ ";
		std::cout <<"   ■■■■■   ■■    ■■  ■■  ■■■■■■■  ■■■         ■■■■■■ ";
		std::cout <<"        ■■■  ■■     ■■ ■■  ■■■■■■■  ■■ ■        ■■         ";
		std::cout <<"■■■  ■■■  ■■      ■■■■  ■■      ■■  ■■   ■      ■■         ";
		std::cout <<"■■■■■■■  ■■        ■■■  ■■      ■■  ■■     ■    ■■■■■■ ";
		std::cout <<"  ■■■■■    ■■          ■■  ■■      ■■  ■■      ■■ ■■■■■■ ";
		std::cout <<"                                                                                " << std::endl;
		setColor(13);
		std::cout <<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ " << std::endl;
		setColor(10);
		std::cout << "【C++ object-oriente Snake game 】\n" << std::endl;
		std::cout << "[UP：↑ ；DOWN：↓ ；LEFT：←；RIGHT：→； PAUSE：Space；]" << std::endl;								
		system("pause");
		system("cls");
	}		

    //Set map width
	int inputMapWidth(void)
	{	
		int width = 0; 
    	std::cout << "Please input width!(20~35)" << std::endl;  
    	std::cout << "width = ";  
    	std::cin >> width;
		while ((width < 20) || (width > 35)) {
			std::cout << "wrong input " << std::endl;
			std::cout << "Please input width!(20~35)" << std::endl;  
        	std::cout << "width = ";  
        	std::cin >> width;	
		}	 
	
		return width;	
	}

	//Set map height
	int inputMapHeight(void)
	{
		int height = 0; 
    	std::cout << "Please input height!(20~35)" << std::endl;  
    	std::cout << "height = ";  
    	std::cin >> height;
		while ((height < 20) || (height > 35)) {
			std::cout << "wrong input " << std::endl;
			std::cout << "Please input height!(20~35)" << std::endl;  
        	std::cout << "height = ";  
        	std::cin >> height;	
		} 
	
		return height;	
	}

	//Set snake length
	int inputSnakeLength()
	{
		int len = 0; 
    	std::cout << "Please input length!(3~6)" << std::endl;
		std::cout << "length = ";  
    	std::cin >> len;  
		while ((len < 3) || (len > 6)) {
			std::cout << "wrong input " << std::endl;
			std::cout << "Please input length!(3~6)" << std::endl;   
        	std::cout << "length = ";  
        	std::cin >> len;	
		}
	
		return len;
	}

    //Set game level
    int setLevel()                        
	{
    	system("cls");
		int level = 0;
	 
		while (1) {
			setColor(12);
			std::cout << "\n\n" ; 
			std::cout << "Please Select Snake Level" << std::endl;
			std::cout << "\n\n";
			std::cout << "1.Easy   2.Normal  3.Hard  4.Impossible " << std::endl;
			std::cout << "\n\n";
			std::cout << "Please enter your choice：";
			std::cin >> level;
	    	if ((level >= 1) && (level <= 4)) {	
		    	break;
	    	}
    	}
    
		system("cls");
	 
		return level;
	}

    //Game interface header information
    void initWindow()  
    {  
        system("mode con cols=80 lines=50");  
        gotoXY(20, 0);  
        setColor(23);  
        std::cout << "Snake" << std::endl;  
        setColor(90);  
        std::cout << "Score:" << std::endl;
	    std::cout << std::endl;  
        std::cout << "by xing." << std::endl;  
    } 

    //Jump coordinates
    void gotoXY(int x, int y)     
    {  
        COORD point;  
        point.X = 2 * x; 
        point.Y = y;
	    HANDLE hOut;  
        hOut = GetStdHandle(STD_OUTPUT_HANDLE);  
        SetConsoleCursorPosition(hOut, point);  
    } 

    //Set output color
    void setColor(int colorId)        
    {
    	HANDLE hOut;  
        hOut = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hOut, colorId);  

    } 

		

}










/*
void Display::gotoPointXY(const Point &p)     //光标跳转到指定位置  
{  
    COORD point;  
    point.X = 2 * p.x;  
    point.Y = p.y;  
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), point);  
} 
*/  
