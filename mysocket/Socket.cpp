#include <iostream>

#include "Socket.h"

#define UNIX_PATH "/tmp/data" 

using std::cout;
using std::endl;

Socket::Socket()
    : m_socketfd(-1)
	, m_acceptfd(-1)
{
}

Socket::~Socket() 
{	  
}

int Socket::initServer(void)
{
	m_socketfd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (-1 == m_socketfd) {  
        cout << "initServer socket error!" << endl;
        return -1;  
    }
    
	struct sockaddr_un ser_addr;  
    ser_addr.sun_family = AF_UNIX;  
    strncpy(ser_addr.sun_path, UNIX_PATH, sizeof(UNIX_PATH));  
	unlink(UNIX_PATH);
	int bindfd = bind(m_socketfd, (struct sockaddr*)&ser_addr, sizeof(ser_addr));
    if (-1 == bindfd) {	
    	cout << "bind error!" << endl;
    	return -1;
    }
    
    int listenfd = listen(m_socketfd, 5);
    if (-1 == listenfd) {	
		cout << "listen error!" << endl;
		return -1;
	}
    
    return 0;
}

int Socket::acceptClient(void)
{
	struct sockaddr_un clt_addr;
	socklen_t len = sizeof(clt_addr); 
	m_acceptfd = accept(m_socketfd, (struct sockaddr*)&clt_addr, &len);
	if (-1 == m_acceptfd) {	
		cout << "accept client error!" << endl; 
		return -1;
	}

	return 0;
}

int Socket::initClient(void)
{
	m_socketfd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (-1 == m_socketfd) { 
        cout << "client socket create fail! " << endl;
        return -1;  
    }
	  
    struct sockaddr_un addr;    
    addr.sun_family = AF_UNIX;  
    strncpy(addr.sun_path, UNIX_PATH, sizeof(UNIX_PATH)); 
	int connectfd = connect(m_socketfd, (struct sockaddr*)&addr, sizeof(addr));
    if (-1 == connectfd) {	
	    cout <<"connect fail!"<< endl;   
        return -1;  
    } 
    
    return 0;
}

int Socket::sendMessage(union sendData *psend)
{
    unsigned char *senData = (unsigned char *)psend;
	if (NULL == psend) {	
		cout << "sendMessage psend error!" << endl;
		return -1 ;
	}
	int sendLen = psend->len + HEADERLEN;
	int sendResult = 0;
    while (sendLen > 0) {
    	if (NULL == senData) {	
		    cout << "sendMessage senddata error!" << endl;
		    return -1 ;
	    }
    	sendResult = send(m_acceptfd, senData, sendLen, 0);
    	if (-1 == sendResult) {	
            cout << "error in mysend!" << endl ;
    	    return -1;
    	}
    	sendLen -= sendResult;
    }
		
    return sendResult;
}

int Socket::recMessage(char* buffer, int bufferNumId)
{
    int tmpLen = 0;
    int header = recv(m_socketfd, &tmpLen, HEADERLEN, 0);
    if(HEADERLEN != header) {
	    cout << "error in recv headerlen,header:" << header << endl;
  	    return -1;
    }
   
    int recMessageLen = 0;
    while (tmpLen > 0) {
  	    if (NULL == buffer) {
		    cout << "recMessage m_pbuff error" << endl;
	  	    return -1;
	    } 
  	        recMessageLen = recv(m_socketfd, buffer + bufferNumId, tmpLen, 0);
  	        if (-1 == recMessageLen) {
		    cout << "error in recv data!" << endl;
  		    return -1;
  	    }
  	    tmpLen -= recMessageLen;
    }
  
    return recMessageLen;  	
}

void Socket::closeSockfd(void)
{
	if (-1 != m_acceptfd) {	
		close(m_acceptfd);
	}
	if (-1 != m_socketfd) {	
		close(m_socketfd);
	}
}


