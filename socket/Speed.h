#ifndef SPEED_H
#define SPEED_H

#include <sys/time.h>

class Speed
{
public:
	Speed();
	virtual ~Speed();
	
	void startTime(void);
	void endTime(void);	
    double tranSpeed(double length);
    
private:
	timeval m_startTime;
	timeval m_endTime;				
};

#endif /*SPEED_H*/
/*EOF*/
