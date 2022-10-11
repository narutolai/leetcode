/*
 **  @file $RCSfile: tmempool.c,v $
 **  general description of this module
 **  $Id: tmempool.c,v 1.7 2009-07-08 01:33:19 kent Exp $
 **  @author $Author: kent ,mickeyxu$
 **  @date $Date: 2009-07-08 01:33:19 $
 **  @version $Revision: 1.7 $
 **  @note Editor: Vim 6.1, Gcc 4.0.1, tab=4
 **  @note Platform: Linux
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "pal/pal.h"
#include "comm/tmempool.h"
#include "pal/ttypes.h"
#include "tmempool_i.h"
#include "comm/comm.h"
#if !defined (_WIN32) && !defined (_WIN64)
#include <unistd.h>
#endif

#define MEMPROTECT
#define TMEMPOOL_INVALID_INDEX  -1

#define TMEMPOOL_IDX2POS(pstPool,idx)   ((idx) % (pstPool)->iMax)

#define TMEMPOOL_INSERT_USED_LINK(pstPool, pstBlock)                    \
{                                                                       \
    if (TMEMPOOL_INVALID_INDEX != (pstPool)->iUsedHead)                   \
    {                                                                           \
        LPTMEMBLOCK pstNext = TMEMPOOL_GET_PTR(pstPool, (pstPool)->iUsedHead);   \
        pstNext->iPrev = TMEMPOOL_IDX2POS(pstPool,(pstBlock)->iIdx);            \
    }                                                                           \
    (pstBlock)->iNext = (pstPool)->iUsedHead;                                   \
    (pstBlock)->iPrev = TMEMPOOL_INVALID_INDEX;                                 \
    (pstPool)->iUsedHead = TMEMPOOL_IDX2POS(pstPool,(pstBlock)->iIdx);          \
    (pstPool)->iUsed++;                                                         \
    (pstBlock)->fValid = 1;                                                     \
}

#define TMEMPOOL_DELE_USED_LINK(pstPool, pstBlock)                             \
do{                                                                             \
    (pstBlock)->fValid = 0;                                                     \
    if (TMEMPOOL_INVALID_INDEX != (pstBlock)->iPrev)                            \
    {                                                                           \
       LPTMEMBLOCK pstPrev =  TMEMPOOL_GET_PTR(pstPool, (pstBlock)->iPrev);      \
       pstPrev->iNext = (pstBlock)->iNext;                                      \
    }else                                                                       \
    {                                                                           \
        pstPool->iUsedHead = TMEMPOOL_IDX2POS(pstPool,(pstBlock)->iNext);       \
    }                                                                           \
    if (TMEMPOOL_INVALID_INDEX != (pstBlock)->iNext)                            \
    {                                                                           \
        LPTMEMBLOCK pstNext =  TMEMPOOL_GET_PTR(pstPool, (pstBlock)->iNext);      \
        pstNext->iPrev = TMEMPOOL_IDX2POS(pstPool,(pstBlock)->iPrev);                                       \
    }                                                                             \
}while(0)

#define TMEMPOOL_INSERT_FREE_LINK_TAIL(pstPool, pstBlock)                       \
{                                                                               \
    (pstBlock)->iNext = TMEMPOOL_INVALID_INDEX;                                 \
    (pstBlock)->fValid = 0;                                                     \
    if(TMEMPOOL_INVALID_INDEX == (pstPool)->iFreeTail )                          \
    {                                                                             \
        (pstPool)->iFreeHead	=	TMEMPOOL_IDX2POS(pstPool,(pstBlock)->iIdx);   \
        (pstPool)->iFreeTail	=	(pstPool)->iFreeHead;                          \
        (pstBlock)->iPrev = TMEMPOOL_INVALID_INDEX;              \
    }else                                                                       \
    {                                                                               \
        LPTMEMBLOCK pstTail	=	TMEMPOOL_GET_PTR(pstPool, (pstPool)->iFreeTail);    \
        pstTail->iNext	=	TMEMPOOL_IDX2POS(pstPool,(pstBlock)->iIdx);             \
        (pstPool)->iFreeTail	=	pstTail->iNext;                                 \
        (pstBlock)->iPrev = TMEMPOOL_IDX2POS(pstPool,(pstTail)->iIdx);             \
    }                                                                               \
}

#define TMEMPOOL_INSERT_FREE_LINK_HEAD(pstPool,pstBlock)                            \
{                                                                                   \
    int iPos = TMEMPOOL_IDX2POS(pstPool,(pstBlock)->iIdx);                          \
    (pstBlock)->iNext =	(pstPool)->iFreeHead;                                       \
    (pstBlock)->fValid = 0;                                                         \
    (pstBlock)->iPrev = TMEMPOOL_INVALID_INDEX;                                     \
    if( TMEMPOOL_INVALID_INDEX == (pstPool)->iFreeHead )                            \
    {                                                                               \
        pstPool->iFreeTail	=	iPos;                                               \
    }else                                                                               \
    {                                                                                \
         LPTMEMBLOCK pstHead =	TMEMPOOL_GET_PTR(pstPool, (pstPool)->iFreeHead); \
         pstHead->iPrev = iPos;                                                       \
    }                                                                               \
    (pstPool)->iFreeHead	=	iPos;                                                   \
}

#define TMEMPOOL_DELETE_FREE_LINK(pstPool, pstBlock)    \
{                                                                                   \
    (pstPool)->iFreeHead = (pstBlock)->iNext;                                       \
    if (TMEMPOOL_INVALID_INDEX == (pstPool)->iFreeHead)                             \
    {                                                                               \
        (pstPool)->iFreeTail = TMEMPOOL_INVALID_INDEX;                              \
    }else                                                                           \
    {                                                                               \
        LPTMEMBLOCK pstHead	=	TMEMPOOL_GET_PTR(pstPool, (pstPool)->iFreeHead);    \
        pstHead->iPrev = TMEMPOOL_INVALID_INDEX;                                    \
    }                                                                               \
}

int tmempool_memprotect(void *addr, size_t len, unsigned long newProt,
		unsigned long *oldProt)

{

	int retVal;
	size_t pageSize;
#if !defined (_WIN32) && !defined (_WIN64)
	pageSize = sysconf(_SC_PAGESIZE);
	size_t alignAddr = ((size_t) addr + pageSize - 1) & ~(pageSize - 1);
	retVal = mprotect((void*) alignAddr, pageSize, newProt);
#else
	unsigned long iNewProt = 0x00;
	if(newProt == PROT_READ)
	iNewProt = PAGE_READONLY;
	else if(newProt == (PROT_READ | PROT_WRITE))
	iNewProt = PAGE_READWRITE;

	retVal = VirtualProtect(addr, len, iNewProt, oldProt);
	if (retVal == 0)
	{
		retVal = -1;
	}
	else
	{
		retVal = 0;
	}
#endif

	return retVal;
}

int tmempool_protect_i(TMEMPOOL *pstPool)
{
	unsigned long oldProp;

    if (NULL == pstPool)
    {
        return -1;
    }

	tmempool_memprotect(pstPool, pstPool->iProtectLen, PROT_READ, &oldProp);
	return 0;

}

int tmempool_unprotect_i(TMEMPOOL *pstPool)
{
	unsigned long oldProp;

    assert(NULL != pstPool);

	tmempool_memprotect(pstPool, pstPool->iProtectLen, PROT_READ | PROT_WRITE,
			&oldProp);
	return 0;

}

int tmempool_get_max_items(TMEMPOOL *pstPool)
{
	if (NULL == pstPool)
    {
		return -1;
    }

	return pstPool->iMax;
}

int tmempool_is_full(TMEMPOOL *pstPool)
{
    if (NULL == pstPool)
    {
        return -1;
    }

	return pstPool->iMax == pstPool->iUsed;
}

int tmempool_destroy(TMEMPOOL** ppstPool)
{
	if (ppstPool && *ppstPool)
	{
		if ((*ppstPool)->iUseProtect)
		{
			tmempool_unprotect_i(*ppstPool);
		}
		if ((*ppstPool)->iIsCalloc)
		{
			free(*ppstPool);
		}
		*ppstPool = NULL;
		return 0;
	}

	return -1;
}

void tmempool_init_head_i(TMEMPOOL* pstPool, int iMax, int iUnit, size_t iSize)
{
	int i;
	char *pszPadding;

    assert(NULL != pstPool);

	pstPool->iMagic = TMEMPOOL_MAGIC;
	pstPool->iBuild = TMEMPOOL_BUILD;

	pstPool->iMax = iMax;
	pstPool->iUnit = iUnit;
	//这个是字节对齐后的
	pstPool->iRealUnit = TMEMPOOL_USER_DATA_UNIT_SIZE(iUnit);
	//这个总大小正好相反
	pstPool->iSize = TMEMPOOL_CALC(iMax, iUnit);
	pstPool->iRealSize = iSize;

	pstPool->iUsed = 0;

	pstPool->iStart = 0;
	pstPool->iEnd = 0;

	pstPool->iFreeHead = -1;
	pstPool->iFreeTail = -1;

	pstPool->iUsedHead = -1;

	pstPool->iLastCursor = -1L;
	pstPool->iIteratorLastCursor = -1L;
	pstPool->iIsIteratorReset = 0;

	pstPool->iMethod = TMEMPOOL_FIFO;

	pstPool->iBlockOff = offsetof(TMEMPOOL,szBlocks);
	pstPool->iBlockSize = TMEMPOOL_BLOCK_SIZE(iMax);

	pstPool->iDataOff = TMEMPOOL_KERNEL_DATA_SIZE(iMax);
	pstPool->iDataSize = TMEMPOOL_DATA_SIZE(iMax,iUnit);

	//    pstPool->iIsPosMethod = 0;
    pstPool->iUseProtect = 0;
	pstPool->iProtectLen = TMEMPOOL_KERNEL_DATA_SIZE(iMax);

	for (i = 0; i < (sizeof(pstPool->szRes) / sizeof(pstPool->szRes[0])); i++)
	{
		pstPool->szRes[i] = sizeof(pstPool->szRes) - i;
	}

	pszPadding = (char *) pstPool + TMEMPOOL_KERNEL_DATA_BASE_SIZE(iMax);
	for (i = 0; i < (pstPool->iDataOff - TMEMPOOL_KERNEL_DATA_BASE_SIZE(iMax)); i++)
	{
		*pszPadding++ = i;
	}

	return;

}

int tmempool_set_opt(TMEMPOOL *pstPool, TMEMPOOLOPT optCode, void *pvData,
		size_t iData)
{
    if (NULL == pstPool)
    {
        return -1;
    }

	switch (optCode)
	{
	case TMEMPOOL_SET_ALLOC_METHOD_FIFO:
		pstPool->iMethod = 1;
		break;

	case TMEMPOOL_SET_ALLOC_METHOD_LIFO:
		pstPool->iMethod = 0;
		break;

	case TMEMPOOL_SET_PAGE_PROTECT:
		pstPool->iUseProtect = 1;
		break;

	case TMEMPOOL_RESET_PAGE_PROTECT:
		pstPool->iUseProtect = 0;
		break;

	default:
		return -1;
		break;
	}
	return 0;
}

void tmempool_init_body_i(TMEMPOOL* pstPool)
{
	TMEMBLOCK* pstTail;
	TMEMBLOCK* pstBlock;
	int i;

    assert(NULL != pstPool);

	if (pstPool->iMax <= 0)
		return;

	pstPool->iFreeHead = 0;	//空闲链表头指针
	pstPool->iFreeTail = 0; //空闲链表表尾指针

	pstTail = TMEMPOOL_GET_PTR(pstPool, pstPool->iFreeTail);
	pstTail->iNext = -1;
	pstTail->fValid = 0;
	memset(&pstTail->iRes, 0, sizeof(pstTail->iRes));
	pstTail->iIdx = 0;
	pstTail->iPrev = -1;
	//这里做的其实就是把索引给链接起来了。
	//把索引链起来，然后设置空闲链表的头指针和尾指针。
	for (i = 1; i < pstPool->iMax; i++)
	{
		pstTail = TMEMPOOL_GET_PTR(pstPool, pstPool->iFreeTail);//空闲链表的最后一个索引块

		pstBlock = TMEMPOOL_GET_PTR(pstPool, i);//当前节点的索引

		pstBlock->fValid = 0;
		memset(&pstBlock->iRes, 0, sizeof(pstTail->iRes));
		pstBlock->iIdx = 0; 
		pstBlock->iNext = -1L;
		//当前索引的上一个
		pstBlock->iPrev = i - 1;

		//尾	指针指向前一个索引，然后让改索引的下一个指向i
		pstTail->iNext = i;
		//空闲链表的指向最后一个索引,更新尾部指针就行了。
		pstPool->iFreeTail = i;
	}

	return;
}

int tmempool_check_head_i(TMEMPOOL* pstPool, int iMax, int iUnit, size_t iSize)
{
    assert(NULL != pstPool);

	if (iSize < TMEMPOOL_HEAD_SIZE)
	{
		return -1;
	}

	if ((TMEMPOOL_MAGIC != pstPool->iMagic) || (TMEMPOOL_BUILD
			!= pstPool->iBuild) || !pstPool->iInited)
		return -1;

	if ((iMax != pstPool->iMax) || (iUnit != pstPool->iUnit))
		return -1;

	if ((iSize < TMEMPOOL_CALC(iMax, iUnit)) || (iSize < pstPool->iRealSize))
		return -1;

	if (pstPool->iStart != pstPool->iEnd)
		return tmempool_fix(pstPool);

	return 0;
}

int tmempool_init(TMEMPOOL** ppstPool, int iMax, size_t iUnit, void* pvBase,
		size_t iSize)
{
	TMEMPOOL* pstHead;
	size_t iNeed;

	if (NULL == ppstPool || NULL == pvBase)
	{
	    return -1;
	}
	if (0 >= iUnit || 0 >= iMax)
	{
	    return -1;
	}

	iNeed = TMEMPOOL_CALC((size_t)iMax, (size_t)iUnit);

	if (iNeed / iUnit < iMax || iNeed > iSize)
		return -1;

	pstHead = (TMEMPOOL*) pvBase;
	tmempool_init_head_i(pstHead, iMax, iUnit, iSize);
	tmempool_init_body_i(pstHead);

	pstHead->iInited = 1;
	*ppstPool = pstHead;
	return 0;
}

int tmempool_new(TMEMPOOL** ppstPool, size_t iMax, size_t iUnit)
{
	size_t iSize = 0;
	if ((0 >= iMax) || 0 >= iUnit)
	{
		return -1;
	}

	iSize = TMEMPOOL_CALC(iMax, iUnit);//根据iMax和iUnit 计算池的总大小

	if (iSize / iUnit < iMax)
	{
		return -1;
	}

	if (!ppstPool)
	{
		return iSize;
	}

	if (iSize < 0)
	{
		return -1;
	}

	*ppstPool = (TMEMPOOL*) calloc(1, iSize);//然后分配内存这个是申请的堆内存吧

	if (!*ppstPool)
		return -1;

	tmempool_init_head_i(*ppstPool, iMax, iUnit, iSize);
	tmempool_init_body_i(*ppstPool);

	(*ppstPool)->iIsCalloc = 1;
	(*ppstPool)->iInited = 1;

	return 0;
}

size_t tmempool_get_size(TMEMPOOL *pstPool)
{
	if (pstPool && pstPool->iInited)
	{
		return pstPool->iSize;
	}
	return -1;
}

int tmempool_attach(TMEMPOOL** ppstPool, int iMax, int iUnit, void* pvBase,
		size_t iSize)
{
	int iRet;

	LPTMEMPOOL pstPool;
	pstPool = (LPTMEMPOOL) pvBase;
	if (NULL == ppstPool || NULL == pvBase)
	{
	    return -1;
	}

	iRet = tmempool_check_head_i(pstPool, iMax, iUnit, iSize);
	if (iRet)
	{
		return -1;
	}

	iRet = tmempool_check_chain_i(pstPool);
	if (iRet == 0)
	{
		*ppstPool = pvBase;
		return 0;
	}

	return -1;

}

size_t tmempool_calc_size(size_t iMax, size_t iUnit)
{
	size_t iSize;
	iSize = TMEMPOOL_CALC(iMax, iUnit);
	return iSize;
}

int tmempool_set_method(TMEMPOOL* pstPool, int iMethod)
{
	int iOld;

    if (NULL == pstPool)
    {
        return -1;
    }

	iOld = pstPool->iMethod;
	pstPool->iMethod = iMethod;

	return iOld;
}

void* tmempool_get(TMEMPOOL* pstPool, int iIdx)
{
	TMEMBLOCK* pstBlock;

    if (NULL == pstPool)
    {
        return NULL;
    }

	if (iIdx < 0)
		return NULL;
	//先获取链表节点
	pstBlock = TMEMPOOL_GET_PTR(pstPool, iIdx);

	if (!pstBlock->fValid || (pstBlock->iIdx != iIdx))
		return NULL;
	else//再由节点获取数据块
		return TMEMPOOL_GET_DATA(pstPool,pstBlock);
}

void* tmempool_get_bypos(TMEMPOOL* pstPool, int iPos)
{
	TMEMBLOCK* pstBlock;

    if (NULL == pstPool)
    {
        return NULL;
    }

	if (iPos < 0)
		return NULL;

	pstBlock = TMEMPOOL_GET_PTR(pstPool, iPos);

	if (!pstBlock->fValid)
		return NULL;
	else
		return TMEMPOOL_GET_DATA(pstPool,pstBlock);
}
//先调用这个获取空闲链表头指针指向的内存索引
int tmempool_alloc(TMEMPOOL* pstPool)
{
	int iPos;
	int iIdx;
	TMEMBLOCK* pstBlock;

    if (NULL == pstPool)
    {
        return -1;
    }

	if (pstPool->iUsed >= pstPool->iMax)
		return -1;

	assert(TMEMPOOL_INVALID_INDEX != pstPool->iFreeHead);
	if (TMEMPOOL_INVALID_INDEX == pstPool->iFreeHead)
	{
		return -2;
	}

	if (pstPool->iStart != pstPool->iEnd)
		return -3;

	if (pstPool->iUseProtect)
		tmempool_unprotect_i(pstPool);

	pstPool->iStart++;

	iPos = pstPool->iFreeHead;
	pstBlock = TMEMPOOL_GET_PTR(pstPool, iPos);
	if (0 == pstBlock->iIdx && 0 == iPos)
	{
		iIdx = pstPool->iMax;
	}
	else
	{	
		//????what fuck ????
		// 卧槽看不懂
		iIdx = (pstBlock->iIdx / pstPool->iMax) * pstPool->iMax + pstPool->iMax + iPos;
		if (iIdx < 0)
		{
			if (0 == iPos)
			{
				iIdx = pstPool->iMax;
			}
			else
			{
				iIdx = iPos;
			}
		}
	}
	pstBlock->iIdx = iIdx;
	pstPool->iLastIdx = iIdx;
	//删除空闲链表
	TMEMPOOL_DELETE_FREE_LINK(pstPool, pstBlock);
	//插入使用链表
	TMEMPOOL_INSERT_USED_LINK(pstPool, pstBlock);

	pstPool->iEnd = pstPool->iStart;

	if (pstPool->iUseProtect)
		tmempool_protect_i(pstPool);

	return iIdx;
}

int tmempool_alloc_bypos(TMEMPOOL* pstPool)
{
	int iPos;
	int iIdx;
	TMEMBLOCK* pstBlock;

    if (NULL == pstPool)
    {
        return -1;
    }

	if (pstPool->iUsed >= pstPool->iMax)
		return -1;

	assert(TMEMPOOL_INVALID_INDEX != pstPool->iFreeHead);

	if (TMEMPOOL_INVALID_INDEX == pstPool->iFreeHead)
	{
		return -2;
	}

	if (pstPool->iStart != pstPool->iEnd)
		return -3;

	if (pstPool->iUseProtect)
		tmempool_unprotect_i(pstPool);

	pstPool->iStart++;

	iPos = pstPool->iFreeHead;
	pstBlock = TMEMPOOL_GET_PTR(pstPool, iPos);
	if (0 == pstBlock->iIdx && 0 == iPos)
	{
		iIdx = pstPool->iMax;
	}
	else
	{
		iIdx = (pstBlock->iIdx / pstPool->iMax) * pstPool->iMax + pstPool->iMax
				+ iPos;
		if (iIdx < 0)
		{
			if (0 == iPos)
			{
				iIdx = pstPool->iMax;
			}
			else
			{
				iIdx = iPos;
			}
		}
	}
	pstBlock->iIdx = iIdx;
	pstPool->iLastIdx = iIdx;

	TMEMPOOL_DELETE_FREE_LINK(pstPool, pstBlock);

	TMEMPOOL_INSERT_USED_LINK(pstPool, pstBlock);

	pstPool->iEnd = pstPool->iStart;

	if (pstPool->iUseProtect)
		tmempool_protect_i(pstPool);

	return iIdx % pstPool->iMax;
}

int tmempool_free(TMEMPOOL* pstPool, int iIdx)
{
	TMEMBLOCK* pstBlock;

    if (NULL == pstPool)
    {
        return -1;
    }

	if (pstPool->iMax <= 0 || iIdx < 0)
		return -1;

	pstBlock = TMEMPOOL_GET_PTR(pstPool, iIdx);
	if (!pstBlock->fValid)
		return -2;
	if (pstBlock->iIdx != iIdx)
		return -3;

	if (pstPool->iStart != pstPool->iEnd)
		return -4;

	if (pstPool->iUseProtect)
		tmempool_unprotect_i(pstPool);

	pstPool->iStart++;
    TMEMPOOL_DELE_USED_LINK(pstPool,pstBlock);
	switch (pstPool->iMethod)
	{
	case TMEMPOOL_LIFO:
		TMEMPOOL_INSERT_FREE_LINK_HEAD(pstPool,pstBlock)
		;
		break;

	default:
		TMEMPOOL_INSERT_FREE_LINK_TAIL(pstPool,pstBlock)
		;
		break;
	}
	pstPool->iUsed--;
	pstPool->iEnd = pstPool->iStart;

	if (pstPool->iUseProtect)
		tmempool_protect_i(pstPool);
	return 0;
}

int tmempool_free_bypos(TMEMPOOL* pstPool, int iIdx)
{
	TMEMBLOCK* pstBlock;

    if (NULL == pstPool)
    {
        return -1;
    }

	if (pstPool->iMax <= 0 || iIdx < 0)
		return -1;

	pstBlock = TMEMPOOL_GET_PTR(pstPool, iIdx);
	if (!pstBlock->fValid)
		return -2;

	if (pstPool->iStart != pstPool->iEnd)
		return -4;

	if (pstPool->iUseProtect)
		tmempool_unprotect_i(pstPool);

	pstPool->iStart++;

    TMEMPOOL_DELE_USED_LINK(pstPool,pstBlock);
	switch (pstPool->iMethod)
	{
	case TMEMPOOL_LIFO:
		TMEMPOOL_INSERT_FREE_LINK_HEAD(pstPool,pstBlock)
		;
		break;

	default:
		TMEMPOOL_INSERT_FREE_LINK_TAIL(pstPool,pstBlock)
		;
		break;
	}

	pstPool->iUsed--;
	pstPool->iEnd = pstPool->iStart;

	if (pstPool->iUseProtect)
		tmempool_protect_i(pstPool);
	return 0;
}

int tmempool_free_byptr(TMEMPOOL *pstPool, void *pvData)
{
    if (NULL == pstPool || NULL == pvData)
    {
        return -1;
    }

	if (TMEMPOOL_IS_INVALIDPTR(pstPool,pvData))
	{
		return -1;
	}

	if ((size_t)pvData < (size_t)pstPool + pstPool->iDataOff)
	{
	    return -1;
	}

	if ((size_t)pvData >= (size_t)pstPool + pstPool->iDataOff + pstPool->iDataSize)
	{
	    return -1;
	}

	return tmempool_free_bypos(pstPool, TMEMPOOL_PTR2POS(pstPool,pvData));
}

int tmempool_check_chain_i(TMEMPOOL *pstPool)
{
	int i;
	TMEMBLOCK *pstBlock;
	int iNfree = 0;
	int iNUsed;
	char *paIsVisited = NULL;
	int idx;
	int iRet = 0;

    if (NULL == pstPool)
    {
        return -1;
    }


	if (0 >= pstPool->iMax)
	{
		return 0;
	}
	paIsVisited = calloc(pstPool->iMax, sizeof(char));
	if (NULL == paIsVisited)
	{
		printf("failed to calloc memory(size:%"PRIuPTR") for check Tmempool\n",
				pstPool->iMax * sizeof(char));
		return -1;
	}

	idx = pstPool->iUsedHead ;
	iNUsed = 0;
	for (i = 0; ((TMEMPOOL_INVALID_INDEX != idx) && (i < pstPool->iMax)); i++)
	{
		pstBlock = TMEMPOOL_GET_PTR(pstPool, idx);
		if (!TMEMBLOCK_IS_VALID(pstBlock))
		{
			printf(	"error:the node(pos:%d) is invalid(fValid:%d), but it's  in the used link of the memppol\n",
					idx, pstBlock->fValid);
			iRet = -2;
			break;
		}
        idx %= pstPool->iMax;
		if (0 != paIsVisited[idx])
		{
			printf(	"error:the node(pos:%d) is finded in the used link of the memppol twice!!\n",
					idx);
			iRet = -3;
			break;
		}
		else
		{
			paIsVisited[idx] = 1;
		}

		iNUsed++;
		idx = pstBlock->iNext ;
	}/*for(i = 0; ((TMEMPOOL_INVALID_INDEX != idx) && (i < pstPool->iMax)) ; i++)*/


	if ((i >= pstPool->iMax) && (TMEMPOOL_INVALID_INDEX != idx))
	{
		printf(	"all node is used in the mempool, but the last node's next pointer is not null\n");
		iRet = -4;
	}
	//
	if (0 == iRet)
	{
		idx = pstPool->iFreeHead;
		iNfree = 0;
		for (i = 0; ((TMEMPOOL_INVALID_INDEX != idx) && (i < pstPool->iMax)); i++)
		{
			pstBlock = TMEMPOOL_GET_PTR(pstPool, idx);
			if (TMEMBLOCK_IS_VALID(pstBlock))
			{
				printf("error:the node(pos:%d) is valid(fValid:%d), but it's  in the free link of the memppol\n",
						idx, pstBlock->fValid);
				iRet = -5;
				break;
			}
            idx %= pstPool->iMax;
			if (0 != paIsVisited[idx])
			{
				printf(
						"error:the node(pos:%d) is finded in the free link of the memppol twice!!\n",
						idx);
				iRet = -6;
				break;
			}
			else
			{
				paIsVisited[idx] = 1;
			}

			iNfree++;
			idx = pstBlock->iNext ;
		}/*for(i = 0; ((TMEMPOOL_INVALID_INDEX != idx) && (i < pstPool->iMax)) ; i++)*/
	}/*if (0 == iRet)*/

	if ((i >= pstPool->iMax) && (TMEMPOOL_INVALID_INDEX != idx))
	{
		printf(	"all node is free in the mempool, but the last node's next pointer is not null\n");
		iRet = -7;
	}

	if ((0 == iRet) && (TMEMPOOL_INVALID_INDEX != pstPool->iFreeTail))
	{
		pstBlock = TMEMPOOL_GET_PTR(pstPool, pstPool->iFreeTail);
		if (TMEMBLOCK_IS_VALID(pstBlock))
		{
			printf(	"error:the node(pos:%d) by freeTail is valid(fValid:%d), but it's  in the free link of the memppol\n",
					pstPool->iFreeTail, pstBlock->fValid);
			iRet = -8;
		}

		if (TMEMPOOL_INVALID_INDEX != pstBlock->iNext)
		{
			printf("the last free node(pos:%d)'s next pointer is not null\n",
					pstPool->iFreeTail);
			iRet = -9;
		}
	}/*if ((0 == iRet) && (TMEMPOOL_INVALID_INDEX != pstPool->iFreeTail))*/

	if (iNUsed + iNfree != pstPool->iMax)
	{
		printf(	"the used node(Count:%d) and the free node(count:%d) is not equal to total node num(%d)\n",
				iNUsed, iNfree, pstPool->iMax);
		iRet = -10;
	}

	if (NULL != paIsVisited)
	{
		free(paIsVisited);
	}
	return iRet;
}

int tmempool_fix(TMEMPOOL* pstPool)
{
	TMEMBLOCK* pstBlock;
	int i;

    if (NULL == pstPool)
    {
        return -1;
    }

	if (pstPool->iStart == pstPool->iEnd)
		return 0;

	pstPool->iFreeTail = -1;
	pstPool->iFreeHead = -1;
	pstPool->iUsedHead = -1;
	pstPool->iUsed = 0;

	if (pstPool->iMax <= 0)
	{
		pstPool->iEnd = pstPool->iStart;
		return 0;
	}

	for (i = 0; i < pstPool->iMax; i++)
	{
		pstBlock = TMEMPOOL_GET_PTR(pstPool, i);

		if (pstBlock->fValid)
		{
			TMEMPOOL_INSERT_USED_LINK(pstPool, pstBlock);
			continue;
		}

		TMEMPOOL_INSERT_FREE_LINK_TAIL(pstPool, pstBlock);
	}

	return 0;
}

int tmempool_find_used_first(TMEMPOOL* pstPool, int* piPos)
{
	int i;
	TMEMBLOCK* pstBlock;

    if (NULL == pstPool || NULL == piPos)
    {
        return -1;
    }

	for (i = 0; i < pstPool->iMax; i++)
	{
		pstBlock = TMEMPOOL_GET_PTR(pstPool, i);

		if (pstBlock->fValid)
		{
			*piPos = i;
			return 0;
		}
	}

	return -1;
}

int tmempool_find_used_next(TMEMPOOL* pstPool, int* piPos)
{
	int i;
	int iIdx;
	int iFind;
	TMEMBLOCK* pstBlock;

    if (NULL == pstPool || NULL == piPos)
    {
        return -1;
    }

	if (-1 == *piPos)
		return -1;

	pstBlock = TMEMPOOL_GET_PTR(pstPool, *piPos);

	iIdx = pstBlock->iIdx;

	iFind = -1;

	for (i = *piPos + 1; i < pstPool->iMax; i++)
	{
		pstBlock = TMEMPOOL_GET_PTR(pstPool, i);

		if (pstBlock->fValid)
		{
			iFind = i;
			break;
		}
	}

	*piPos = iFind;

	return iIdx;
}

int tmempool_travel_all(IN TMEMPOOL *pstPool, TMEMPOOL_TRAVEL_FUNC pfnTravel, void* pvArg)
{
    int i;
    int iRet;

    if (NULL == pstPool || NULL == pfnTravel)
    {
        return -1;
    }

    for (i = 0; i < pstPool->iMax; i++)
    {
        void* pvData = TMEMPOOL_GET_DATA_I(pstPool, i);

        iRet = pfnTravel(pvData, pvArg);
        if (0 != iRet)
        {
            return iRet;
        }
    }

    return 0;
}

int tmempool_travel_used(IN TMEMPOOL *pstPool, TMEMPOOL_TRAVEL_FUNC pfnTravel, void* pvArg)
{
    int i = 0;
    int iRet = 0;
    int idx = TMEMPOOL_INVALID_INDEX;

    if (NULL == pstPool || NULL == pfnTravel)
    {
        return -1;
    }

    idx = pstPool->iUsedHead;
    for (i = 0; ((idx != TMEMPOOL_INVALID_INDEX) && (i < pstPool->iMax)); i++)
    {
		TMEMBLOCK* pstBlock = TMEMPOOL_GET_PTR(pstPool, idx);
		if (!TMEMBLOCK_IS_VALID(pstBlock))
		{
            return -2;
		}

        idx = pstBlock->iNext;
        iRet = pfnTravel(TMEMPOOL_GET_DATA(pstPool,pstBlock), pvArg);
        if (0 != iRet)
        {
            return iRet;
        }
    }

    return 0;
}

int tmempool_get_used_items(TMEMPOOL* pstPool)
{
    if (NULL == pstPool)
    {
        return -1;
    }

	return pstPool->iUsed;
}

int tmempool_print_block_i(TMEMPOOL *pstPool, TMEMBLOCK *pstBlock, FILE *fp)
{
    assert(NULL != pstPool);
    assert(NULL != pstBlock);
    assert(NULL != fp);

	fprintf(fp, "Block:{\n");
	fprintf(fp, "  Index=%" "d" "\n", pstBlock->iIdx);
	fprintf(fp, "  RealOffset=%"PRIuPTR"\n", (intptr_t) pstBlock->iIdx % pstPool->iMax);
	fprintf(fp, "  fValid=%" "d" "\n", pstBlock->fValid);
	fprintf(fp, "  }\n");
	return 0;
}

int tmempool_dump_used(TMEMPOOL *pstPool, FILE *fp)
{
	int i;
	LPTMEMBLOCK pstBlock;

    if (NULL == pstPool || NULL == fp)
    {
        return -1;
    }


	fprintf(fp, "############################\n");
	fprintf(fp, "Tmempool:%"PRIuPTR"\n", (intptr_t) pstPool);
	fprintf(fp, "Tmempool->iMax:%" "d" "\n", pstPool->iMax);
	fprintf(fp, "Tmempool->iUsed:%"PRIuPTR"\n", pstPool->iUsed);
	fprintf(fp, "Tmempool->iCurrent:%"PRIuPTR"\n", pstPool->iIteratorLastCursor);

	for (i = 0; i < pstPool->iMax; i++)
	{
		pstBlock = TMEMPOOL_GET_PTR(pstPool, i);

		if (pstBlock->fValid)
		{
			fprintf(fp, "Tmempool:%d\n", pstBlock->iIdx);
		}
	}

	fprintf(fp, "===========================\n");

	return 0;
}

int tmempool_ptr2idx(IN TMEMPOOL *pstPool, void *pvData)
{
    LPTMEMBLOCK pstBlock;
    int iPos;

    if (NULL == pstPool || NULL == pvData)
    {
        return -1;
    }

    if ((size_t) pvData < (size_t) pstPool + pstPool->iDataOff)
    {
        return -1;
    }

    if ((size_t) pvData >= (size_t) pstPool + pstPool->iDataOff
        + pstPool->iDataSize)
    {
        return -1;
    }

    if (pstPool->iRealUnit <= 0)
    {
        return -1;
    }

    //assert(0 == ( ((size_t)pvData - ((size_t)pstPool+pstPool->iDataOff)) % pstPool->iDataSize ));
    iPos = TMEMPOOL_PTR2POS(pstPool, pvData);

    pstBlock = TMEMPOOL_GET_PTR(pstPool,iPos);
    if (!pstBlock->fValid)
    {
        return -1;
    }

    return pstBlock->iIdx;
}
