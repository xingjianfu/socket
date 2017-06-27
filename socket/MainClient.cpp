#include <iostream>

#include "Client.h"

#define ERROR -1

using std::cout;
using std::endl;

int main()
{
	int ret = 0;
	
	Client *pClinet = new Client();
	if (NULL == pClinet) {
		cout << "new pClient error!" << endl;
		return -1;
	}
	
	do {
		if (pClinet->initClientSocket() == ERROR) {
			cout << "init client socket error!" << endl;
			ret = -1; 
			break;
		}
		
		if (pClinet->clientRecData() == ERROR) {	
			cout<< "client revcdata error!" << endl;
			ret = -1;
			break;
		}	
		
		 cout << "client revcdata success!" << endl;
		 	 
	} while(0);
     
	pClinet->closeSocket();
	
	if(NULL != pClinet) {	
		delete pClinet;
        pClinet = NULL;
	}
	
	return ret;		
}














/*
int main()
{
	int ret=0;
	
	Client *pClinet = new Client();
	
    if(pClinet->socketClientinit()<0)
	{
		cout<<"client init error!"<<endl;
		return -1;
	}
    
    pClinet->client_recdata();
   
    pClinet->Clientclosesock();
    
	delete pClinet;
	
	return ret;	
}
*/
