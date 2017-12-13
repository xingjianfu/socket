#ifndef CLIENT_H
#define CLIENT_H

#include "Filerw.h"
#include "Speed.h"
#include "Socket.h"

class Client
{
public:
    Client();
    virtual ~Client();
    
    int initClientSocket(void);
    int clientRecData(void);
	void closeSocket(void);
			
private:
	Socket *m_pClientSocket;
	Filerw *m_pClientFile;
	Speed *m_pClientSpeed;
    char *m_pbuff; 
    int m_bufferNumId;
    const char *m_pOutFile;
    
    template <typename T>
    void news(T **p);
	template <typename T>
    void release(T **p);
};

#endif /*CLIENT_H*/
/*EOF*/
