/*
**  @file $RCSfile: tmempool_shm.c,v $
**  general description of this module
**  $Id: tmempool_shm.c,v 1.1.1.1 2008-05-28 07:35:00 kent Exp $
**  @author $Author: kent $
**  @date $Date: 2008-05-28 07:35:00 $
**  @version $Revision: 1.1.1.1 $
**  @note Editor: Vim 6.1, Gcc 4.0.1, tab=4
**  @note Platform: Linux
*/

#include "pal/pal.h"

#include "comm/tmempool.h"
#include "comm/tmempool_shm.h"
#include "tmempool_i.h"

int tmempool_new_shm(TMEMPOOL** ppstPool, key_t uiKey, int iMax, int iUnit)
{
	HANDLE iShmID=(HANDLE)(-1);
	size_t iSize=0;
	void* pvAddr=NULL;
	int iIsExist=0;
	int iRet;

	iSize	=	TMEMPOOL_CALC(iMax, iUnit);
	if( iSize<= 0 )
		return -1;

	iShmID	=	shmget(uiKey, iSize, 0666 | IPC_CREAT | IPC_EXCL);

	if( iShmID<0 )
	{
		iIsExist	=	1;
		iShmID		=	shmget(uiKey, iSize, 0666);
	}

	if( iShmID<0 )
		return -1;

	pvAddr	=	shmat(iShmID, NULL, 0);

	if( (void *) -1 == pvAddr )
		return -1;

	if( iIsExist )
		iRet	=	tmempool_attach(ppstPool, iMax, iUnit, pvAddr, iSize);
	else
		iRet	=	tmempool_init(ppstPool, iMax, iUnit, pvAddr, iSize);

	if( iRet<0 )
		shmdt(pvAddr);

	return iRet;
}

