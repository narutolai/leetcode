#ifndef TMEMPOOL_I_H__
#define TMEMPOOL_I_H__

#include "comm/tlist.h"
#include "commbase_i.h"

#define TMEMPOOL_MAGIC			0x4324
#define TMEMPOOL_BUILD			2

#define TMEMPOOL_PAGE_SIZE      8192    //内存页的大小
#define TMEMPOOL_USER_DATA_ALIGN    8   //用户数据对齐字节数
//就是和mysql的一模一样....... 这个就是这个节点
struct tagTMemBlock
{
	int fValid;
	int iIdx;
	int iPrev;
	int iNext;
	int iRes;
};

typedef struct tagTMemBlock TMEMBLOCK;
typedef struct tagTMemBlock *LPTMEMBLOCK;

#define TMEMBLOCK_IS_VALID(p)	((p)->fValid)

//怀疑是仿照mysql的BufferPool
struct tagTMemPool
{
	int iMagic; //用于检查mempool内存
	int iBuild; //用于检查mempool内存
	int iMax;//mempool的容量

	int iFreeHead; //空闲链表头指针
	int iFreeTail;//空闲链表尾指针
	int iUsedHead; //使用链表头指针
	size_t iUsed;//有多少memblock已经被使用

	int iLastIdx;//最后分配的memblock索引
	int iInited;//mempool是否经过了初始化
	int iIsCalloc;//mempool是否分配过内存
	int iMethod;//TMEMPOOL_FIFO  memblock分配采用先进先出,是默认的方法; TMEMPOOL_LIFO

	volatile int iStart;//内部使用，与iEnd配合检验tmempool_alloc和tmempool_free操作的原子性
	volatile int iEnd;

	size_t iUnit;//应用数据的大小
	size_t iRealUnit;//在mempool中考虑圆整后数据占用内存的大小
	size_t iSize;//mempool占用内存的大小
	size_t iRealSize;//与iSize相同, 考虑字节对齐后的占用内存的大小


	size_t iBlockOff;
	size_t iBlockSize;

	size_t iDataOff;
	size_t iDataSize;

	intptr_t iLastCursor;
	intptr_t iIteratorLastCursor;
	int iIsIteratorReset;

	int iUseProtect;
	size_t iProtectLen;

	char szRes[64];//预留

	//以下是数据索引区和数据区
	TMEMBLOCK szBlocks[1];//数据区起始位置
};

#define TMEMPOOL_ROUND(unit, round)	( ( ( (intptr_t)(unit) + (intptr_t)(round) - 1 ) / (intptr_t)(round) ) * (intptr_t)(round) )

#define TMEMPOOL_HEAD_SIZE   (offsetof(TMEMPOOL, szBlocks))

#define TMEMPOOL_BLOCK_SIZE(iMax) (iMax * sizeof(TMEMBLOCK))//这个block是数据索引
//核的总大小就是头的大小加上索引的大小
#define TMEMPOOL_KERNEL_DATA_BASE_SIZE(iMax)   (TMEMPOOL_HEAD_SIZE + TMEMPOOL_BLOCK_SIZE(iMax) )

/*mempool 头部信息区加数据索引区的大小，这两部大小会按照内存页大小对齐，
 以便实现按页保护
 //按照4KB对齐
 */
#define TMEMPOOL_KERNEL_DATA_SIZE(iMax)   TMEMPOOL_ROUND(TMEMPOOL_KERNEL_DATA_BASE_SIZE(iMax),TMEMPOOL_PAGE_SIZE)

#define TMEMPOOL_USER_DATA_UNIT_SIZE(iSize)  TMEMPOOL_ROUND(iSize,TMEMPOOL_USER_DATA_ALIGN)
//单个obj 8字节对齐 ，，，真的是为了性能无所不用其及
#define TMEMPOOL_DATA_SIZE(iMax,iSize) (iMax * TMEMPOOL_USER_DATA_UNIT_SIZE(iSize))

//mempool的总大小 内存对齐(头+索引总大小) + 内存对齐(用户obj)
#define TMEMPOOL_CALC(iMax,iUnit)  (TMEMPOOL_KERNEL_DATA_SIZE(iMax) + TMEMPOOL_DATA_SIZE(iMax,iUnit))
//根据idx 下标?获取索引
#define TMEMPOOL_GET_PTR(pstPool, idx)	((LPTMEMBLOCK)((pstPool)->szBlocks + ((size_t)(idx) % (pstPool)->iMax) ))
//这个idx是索引中的id指向索引数据的位置
#define TMEMPOOL_GET_DATA_I(pstPool,idx)  ((void *)((size_t)(pstPool)+(pstPool)->iDataOff + (pstPool)->iRealUnit * ((size_t)(idx) % (pstPool)->iMax )))
//传入索引获取数据
#define TMEMPOOL_GET_DATA(pstPool,pstBlock)  TMEMPOOL_GET_DATA_I(pstPool,(pstBlock)->iIdx)

#define TMEMPOOL_GET_CAP(pool)		((pool)->iMax)
#define TMEMPOOL_GET_BLOCK_IDX(blk)	((blk)->iIdx)

#define TMEMPOOL_IS_INVALIDPTR(pstPool,pvData) (((size_t)(pvData) - (size_t)(pstPool)- (size_t)(pstPool)->iDataOff)%(pstPool)->iRealUnit)
//卧槽了呀
#define TMEMPOOL_PTR2POS(pstPool,pvData) (((size_t)(pvData) - (size_t)(pstPool)- (size_t)(pstPool)->iDataOff)/(pstPool)->iRealUnit)

void tmempool_init_head_i(TMEMPOOL* pstPool, int iMax, int iUnit, size_t iSize);
void tmempool_init_body_i(TMEMPOOL* pstPool);
int tmempool_check_head_i(TMEMPOOL* pstPool, int iMax, int iUnit, size_t iSize);
int tmempool_check_chain_i(TMEMPOOL *pstPool);

#endif

