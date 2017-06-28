#include <iostream>

#include "Speed.h"

using std::cout;
using std::endl;

Speed::Speed()
{
}

Speed::~Speed()
{	
}

void Speed::startTime(void)
{
    gettimeofday(&m_startTime, 0);
}

void Speed::endTime(void)
{
    gettimeofday(&m_endTime, 0);
}

double Speed::tranSpeed(double transLength)
{
	double tStart = m_startTime.tv_sec + (double)m_startTime.tv_usec/1000000.0;
    double tEnd = m_endTime.tv_sec + (double)m_endTime.tv_usec/1000000.0;
    double transTime = tEnd-tStart;
    double speed = 0;
    if(0 != transTime)
    {
    	speed = transLength/transTime;
	}
    speed = speed/1000000.0;
    cout << "transtime is" << transTime << endl;
    cout << "speed is:" << speed << "MBps" << endl;
}
