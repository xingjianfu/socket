#ifndef FILERW_H
#define FILERW_H

#include <stdio.h> 

#define PACKETLEN  8192
#define MESSAGE_LENGTH 8190
#define HEADERLEN  2

enum RWResult
{
	RWResult_Read_Success,
	RWResult_Read_Error,
	RWResult_Read_End_File,
	RWResult_Write_Success,
	RWResult_Write_Error	
};

union sendData
{
    short len; 
    unsigned char data[PACKETLEN];
};

class Filerw
{
public:
	Filerw();
	virtual ~Filerw();
	
	int openFile(const char* name);
	int readFile(union sendData* pdata);
	RWResult judgeReadResult(int result);
	int writeFile(const char* buffer, int bufferNumId);
	//RWResult judgeWriteResult(int result);
	void closeFile(FILE* fp);
	
private:
	FILE* m_fp;
};

#endif /*FILERW_H*/
/*EOF*/
