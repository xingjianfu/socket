#include <iostream>

#include "Filerw.h"

using std::cout;
using std::endl;

Filerw::Filerw()
    : m_fp(NULL)
{
}

Filerw::~Filerw()
{
	closeFile(m_fp);	
}

int Filerw::openFile(const char* file)
{
	if (NULL == file) {	
		cout << "openFile error!" << endl;
		return -1;
	}	
	m_fp = fopen(file, "r+");
	if (NULL == m_fp) {	
    	cout << "can't open " << file << " for read" << endl;
    	return -1;
	}	
	    return 0;
}

int Filerw::readFile(union sendData * pdata)
{
	if (NULL == pdata) {
		cout << "readFile pdata error" << endl;
		return -1;
	}
	int readLen = fread(pdata->data + HEADERLEN, 1, MESSAGE_LENGTH, m_fp);
	
	return readLen;
}

RWResult Filerw::judgeReadResult(int reResult)
{
	RWResult reStatus;
	if(MESSAGE_LENGTH == reResult) {
    	reStatus = RWResult_Read_Success;
    	return reStatus;
	}
	else {
		int err = ferror(m_fp);
	    if(0 != err) {
		    cout << "readFile error: read error number is" << err << endl;
		    reStatus = RWResult_Read_Error;
		    return reStatus;
	    }
	    int eof = feof(m_fp);
	    if (0 != eof) {	
		    cout << "end of the file" << endl;
		    reStatus = RWResult_Read_End_File;
		    return reStatus;
	    }
		
	    reStatus = RWResult_Read_Success;	
	}
	
	return reStatus;
}

int Filerw::writeFile(const char* buffer, int byteNumber)
{
	
	if (NULL == buffer) {	
		cout << "writeFile buffer error!" << endl;
		return -1;
	}
	RWResult writeResult;
	int writeLen = 0;
	writeLen = fwrite(buffer, byteNumber, 1, m_fp);
	if(writeLen != byteNumber)
	{
		int err = ferror(m_fp);
	    if (0 != err) {
	    	cout << "write error:" << "error number is" << err << endl;
	        writeResult = RWResult_Write_Error;
	    }
	}
	writeResult = RWResult_Write_Success;
	
	return writeResult;		
}

void Filerw::closeFile(FILE* fp)
{
	if (NULL != fp) {
		fclose(fp);
	}	 
}







/*
int Filerw::fileread(union senddata * pdata)
{
	int ret = 0;
	readlen = 0;
	
	if(NULL == pdata) 
	{
		cout <<"fileread pdata error";
		return -1;
	}
	
	do
	{
		if(ferror(m_fp))
		{
			cout <<"read error" <<endl;
			ret = -1;
			break;
		}
		
		if(feof(m_fp))
		{
			cout <<"end of the file" <<endl;
			ret = END_FILE;
			break;
		}
		readlen=fread(pdata->data+HEADERLEN,1,PACKETLEN-HEADERLEN,m_fp);
		pdata->len = readlen;
		if(readlen == PACKETLEN-HEADERLEN)
		{
			cout<<"read "<<PACKETLEN-HEADERLEN<<endl;
			break;
		} 
	}while(feof(m_fp) || ferror(m_fp));	
	
	
	return ret;
}
*/

/*
int Filerw::filewrite(const char* buffer,int idx)
{
	int ret = 0,writelen = 0 ;
	if(NULL == buffer)
	{
		cout <<"filewrite buffer error"<<endl;
		return -1;
	}
	do
	{
		if(ferror(fp))
		{
			cout <<"write error" <<endl;
			ret = -1;
			break;
		}
		writelen = fwrite(buffer,idx,1,fp);
		if(writelen == idx)
		{
			break;
		} 
	}while(ferror(fp));	
	return ret;
}
*/

