//接口
class IHandlerPool
{
    public:
        virtual ~IHandlerPool() {}

        virtual int Init(size_t a_tItemNum) = 0;
        virtual void* NewHandler() = 0;
        virtual void FreeHandler(int a_iIdx) = 0;
        virtual void* GetHandler(int a_iIdx) = 0;
        virtual void* GetHandlerByPos(int a_iPos) = 0;
        virtual int GetCapacity() const = 0;
        virtual int GetUsedItemNum() const = 0;
};

//类实现接口 实现方法
template <typename HandlerType>
class THandlerPool : public IHandlerPool
{
    public:
        THandlerPool();
        ~THandlerPool();

        virtual int Init(size_t a_tItemNum);
        virtual void* NewHandler();
        virtual void FreeHandler(int a_iIdx);
        virtual void* GetHandler(int a_iIdx);
        virtual void* GetHandlerByPos(int a_iPos);
        virtual int GetCapacity() const;
        virtual int GetUsedItemNum() const;

    public:
        typedef TMEMPOOL_TRAVEL_FUNC FUNCTION_TYPE;
        int TravelAll(FUNCTION_TYPE function, void* a_pvArg);

    private:
        size_t m_tItemNum;
        size_t m_tUnitSize;
        TMEMPOOL* m_pstRawPool;
};
