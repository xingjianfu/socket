#include <iostream>

#include "Client.h"

#define BUFLEN (256*1024)
#define FILE_OUT "out"

using std::cout;
using std::endl;

Client::Client()
    : m_pClientSocket(NULL)
	, m_pClientFile(NULL)
	, m_pClientSpeed(NULL)
	, m_pbuff(NULL)
	, m_bufferNumId(0)
	, m_pOutFile(FILE_OUT)
{
	news(&m_pClientSocket);
	news(&m_pClientFile);
	news(&m_pClientSpeed);
	
	m_pbuff = new char[BUFLEN];
	if (NULL == m_pbuff) {	
	    cout << "new m_pbuff error!" << endl;
	}	
}

Client::~Client()
{
	release(&m_pClientSocket);
	release(&m_pClientFile);
	release(&m_pClientSpeed);	
	if (NULL != m_pbuff) {	
		delete []m_pbuff;
		m_pbuff = NULL;
	}	
}

int Client::initClientSocket(void)
{
	if (NULL == m_pClientSocket) {	
	    cout << "initClientSocket m_pClientSocket error!" << endl;
		return -1;
	}
	
	if (-1 == m_pClientSocket->initClient()) {	
		return -1;
	}
	else {	
		return 0;
	}
}

int Client::clientRecData(void)
{
  
    if (NULL == m_pClientFile) {
	    cout << "recClientData m_pClientFile error!" << endl;
  	    return -1;
    }
    int openfd = m_pClientFile->openFile(m_pOutFile);
    if (-1 == openfd) {
	    return -1;
    }
  
    if (NULL == m_pClientSpeed) {
	    cout << "recClientData m_pClientSpeed error!";
  	    return -1; 	
    }
    m_pClientSpeed->startTime();
    
    int transLen = 0;
    int recMessageLen = 1;
    while (recMessageLen > 0) {
    	if (NULL == m_pClientSocket) {
	        cout << "recClientData m_pClientSocket error!";
  	        return -1; 	
        }
  	    recMessageLen = m_pClientSocket->recMessage(m_pbuff, m_bufferNumId);
  	    if (-1 == recMessageLen) {
  		    return -1;
	    }
	    m_bufferNumId += recMessageLen;
	    
	    transLen += recMessageLen;
	    
  	    if (MESSAGE_LENGTH > BUFLEN - m_bufferNumId) {
		    int writeResult = m_pClientFile->writeFile(m_pbuff, m_bufferNumId);
  		    if (RWResult_Write_Error == writeResult) {
			    return -1;
		    }
		    m_bufferNumId = 0;
	    }
  	
  	    if (recMessageLen < MESSAGE_LENGTH) {
  	        break;
	    }
  	    
    }
    
    if (0 != m_bufferNumId) {
	    int writeResult = m_pClientFile->writeFile(m_pbuff, m_bufferNumId);
  		if (RWResult_Write_Error == writeResult) {
			return -1;
		}
  	    m_bufferNumId = 0;  	
    }
    
    m_pClientSpeed->endTime();
	m_pClientSpeed->tranSpeed(transLen);
   
    return 0;   
}

void Client::closeSocket()
{
	if (NULL == m_pClientSocket) {	
	    cout << "closeClientSock m_pClientSocket error" << endl;
	}
	m_pClientSocket->closeSockfd();
}

template <typename T>
void Client::news(T **p)
{
	*p = new T();
	if (NULL == *p) {	
		cout << "news error!" << endl;	
	}
}

template <typename T>
void Client::release(T **p) 
{
	if (NULL != *p) {	
		delete *p;
		*p = NULL;
	}
}



/*
	m_clientsocket = new Socket();
	if(NULL == m_clientsocket)
	{
		cout<< "error m_clientsocket is NULL" <<endl;
	}
	
	m_pclientfile = new Filerw();
	if(NULL == m_pclientfile)
	{
		cout<< "error m_pclientfile is NULL" <<endl;
	}
	
	m_pclientspeed = new Speed();
	if(NULL == m_pclientspeed)
	{
		cout<< "error m_pclientspeed is NULL" <<endl;
	}
	
	m_buff = new char[BUFLEN];
	if(NULL == m_buff)
	{
		cout<< "error buff is NULL" <<endl;
	}
	*/
