#ifndef SOCKET_H
#define SOCKET_H

#include <sys/socket.h>  
#include <sys/un.h>    
#include <unistd.h>

#include "Filerw.h"

class Socket
{
public:
	Socket();
    virtual ~Socket();
    
	int initServer(void);
	int acceptClient(void);
	int initClient(void);
	int sendMessage(union sendData *psend);
	int recMessage(char* buffer, int byteNumber);
	void closeSockfd(void);
			
private:
	int m_socketfd;
	int m_acceptfd;	
};

#endif /*SOCKET_H*/
/*EOF*/
