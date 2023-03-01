#include "StdAfx.h"
#include "BaseFunc.h"

void MyLogSave (const char* pszName, const char* fmt, ...)
{	
	if (!pszName || !fmt)
		return;

	time_t ltime;
	time( &ltime );

	struct tm *pTime;
	pTime = localtime( &ltime );

	char buffer[1024];
	vsprintf( buffer, fmt, (char*) ((&fmt)+1) );

	char szLogName[256];
	sprintf(szLogName, "%s %d-%d-%d.log", pszName, pTime->tm_year+1900, (pTime->tm_mon+1)/*%12*/, pTime->tm_mday);

	FILE* fp	=fopen(szLogName, "a+");
	if(!fp)
		return;

	fprintf(fp, "%s -- %s", buffer, ctime(&ltime));
	fclose(fp);	
}