#ifndef SERVER_H
#define SERVER_H

#include "Filerw.h"
#include "Speed.h"
#include "Socket.h"

class Server
{
public:
	Server();
    virtual ~Server(); 
    
	int initServerSocket(void);
	int acceptClientSocket(void);
	int serverSendData(void);
	void closeSocket(void);
	
private:
	Socket *m_pServerSocket;
	Filerw *m_pServerFile;
    Speed *m_pServerSpeed;
    const char *m_pInFile;
    
    template <typename T>
    void news(T **p);
	template <typename T>
	void release(T **p);
};

#endif /*SERVER_H*/
/*EOF*/
