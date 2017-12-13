#include<iostream>

#include "Server.h"

#define FILE_IN	"in"

using std::cout;
using std::endl;

Server::Server()
    : m_pServerSocket(NULL)
	, m_pServerFile(NULL)
	, m_pServerSpeed(NULL)
	, m_pInFile(FILE_IN)
{	
	news(&m_pServerSocket);
	news(&m_pServerFile);
	news(&m_pServerSpeed);	
}

Server::~Server()
{
	release(&m_pServerSocket);
	release(&m_pServerFile);
	release(&m_pServerSpeed);	
}

int Server::initServerSocket(void)
{
	if (NULL == m_pServerSocket) {	
		cout << "initServerSocket m_pServerSocket error!" << endl;
		return -1;
	}
	
	if (-1 == m_pServerSocket->initServer()) {	
		return -1;
	}
	else {	
		return 0;
	}
}

int Server::acceptClientSocket(void)
{
	if (NULL == m_pServerSocket) {	
		cout << "acceptClientSocket m_pServerSocket error!" << endl;
		return -1;
	}
	
	if (-1 == m_pServerSocket->acceptClient()) {	
		return -1;
	}
	else {	
		return 0;
	}
}

int Server::serverSendData(void)
{	
    if (NULL == m_pServerFile) {
        cout << "serverSendata m_pServerFile error!" << endl;
  	    return -1;
    }
    int openfd = m_pServerFile->openFile(m_pInFile);
    if (-1 == openfd) {
  	    return -1;
    }
    
    if (NULL == m_pServerSpeed) {
  	    cout <<"serverSendata m_pServerSpeed error!" << endl;
  	    return -1;
    }
    m_pServerSpeed->startTime();
    
    int transLen = 0;
    int readLen = 0;
    int judgeResult = 0;
    union sendData readBuffer;
    do {
	    readLen = m_pServerFile->readFile(&readBuffer);
	    judgeResult = m_pServerFile->judgeReadResult(readLen);
	    if(RWResult_Read_Error == judgeResult) {
			return -1;	
	    }
        readBuffer.len = readLen;
	    if (NULL == m_pServerSocket) {
            cout << "serverSendata m_pServerSocket error!" << endl;
  	        return -1;
        }
  	    int sendLen = m_pServerSocket->sendMessage(&readBuffer);
	    if (-1 == sendLen) {	
		    return -1;
	    }
	
        int realSendLen = sendLen - HEADERLEN;
	    transLen += realSendLen;
	    
    } while(RWResult_Read_End_File != judgeResult);
   
	m_pServerSpeed->endTime();
	m_pServerSpeed->tranSpeed(transLen);
	
	return 0;		
}

void Server::closeSocket(void)
{
	if (NULL == m_pServerSocket) {	
	    cout << "closeServerSocket m_pServerSocket error" << endl;
	}
	m_pServerSocket->closeSockfd();	
}

template <typename T>
void Server::news(T **p)
{
	*p = new T();
	if (NULL == *p) {	
		cout << "news error!" << endl;	
	}
}

template <typename T>
void Server::release(T **p) 
{
	if (NULL != *p) {	
		delete *p;
		*p = NULL;
	}
}





/*
	m_pServerSocket = new Socket();
	if(NULL == m_pServerSocket)
	{
		cout<< "news m_pServerSocket error" <<endl;
	}

	m_pServerFile = new Filerw();
	if(NULL == m_pServerFile)
	{
		cout<< "news m_pServerFile error" <<endl;
	}
	
	m_pServerSpeed = new Speed();
	if(NULL == m_pServerSpeed)
	{
		cout<< "news m_pServerSpeed error" <<endl;
	}
*/
