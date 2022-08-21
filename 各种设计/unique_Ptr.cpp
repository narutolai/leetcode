template<typename T>
class MyUniquePtr
{
public:
   explicit MyUniquePtr(T* ptr = nullptr)
        :mPtr(ptr)
    {}

    ~MyUniquePtr()
    {
        if(mPtr)
            delete mPtr;
    }

    MyUniquePtr(MyUniquePtr &&p) noexcept;
    MyUniquePtr& operator=(MyUniquePtr &&p) noexcept;

    MyUniquePtr(const MyUniquePtr &p) = delete;//将移动构造和拷贝构造直接设置未false
    MyUniquePtr& operator=(const MyUniquePtr &p) = delete;

    T* operator->() const noexcept {return mPtr;}
    T& operator*()const noexcept {return *mPtr;}
    explicit operator bool() const noexcept{return mPtr;}

    void reset(T* q = nullptr) noexcept
    {
        if(q != mPtr){
            if(mPtr)
                delete mPtr;
            mPtr = q;
        }
    }

    T* release() noexcept
    {
        T* res = mPtr;
        mPtr = nullptr;
        return res;
    }
    T* get() const noexcept {return mPtr;}
    void swap(MyUniquePtr &p) noexcept
    {
        using std::swap;
        swap(mPtr, p.mPtr);
    }
private:
    T* mPtr;
};

template<typename T>
MyUniquePtr<T>& MyUniquePtr<T>::operator=(MyUniquePtr &&p) noexcept
{
    swap(*this, p);
    return *this;
}

template<typename T>
MyUniquePtr<T> :: MyUniquePtr(MyUniquePtr &&p) noexcept : mPtr(p.mPtr)
{
    p.mPtr == NULL;
}



#include<iostream>
#include<mutex>
#include<thread>
using namespace std;

template<class T>
class Shared_Ptr{
public:
	Shared_Ptr(T* ptr = nullptr)
		:_pPtr(ptr)
		, _pRefCount(new int(1))
		, _pMutex(new mutex)
	{}
	~Shared_Ptr()
	{
		Release();
	}
	Shared_Ptr(const Shared_Ptr<T>& sp)
		:_pPtr(sp._pPtr)
		, _pRefCount(sp._pRefCount)
		, _pMutex(sp._pMutex)
	{
		AddRefCount();
	}
	Shared_Ptr<T>& operator=(const Shared_Ptr<T>& sp)
	{
		//if (this != &sp)
		if (_pPtr != sp._pPtr)
		{
			// 释放管理的旧资源
			Release();
			// 共享管理新对象的资源，并增加引用计数
			_pPtr = sp._pPtr;
			_pRefCount = sp._pRefCount;
			_pMutex = sp._pMutex;
			AddRefCount();
		}
		return *this;
	}
	T& operator*(){
		return *_pPtr;
	}
	T* operator->(){
		return _pPtr;
	}
	int UseCount() { return *_pRefCount; }
	T* Get() { return _pPtr; }
	void AddRefCount()
	{
		_pMutex->lock();
		++(*_pRefCount);
		_pMutex->unlock();
	}
private:
	void Release()
	{
		bool deleteflag = false;
		_pMutex->lock();
		if (--(*_pRefCount) == 0)
		{
			delete _pRefCount;
			delete _pPtr;
			deleteflag = true;
		}
		_pMutex->unlock();
		if (deleteflag == true)
			delete _pMutex;
	}
private:
	int *_pRefCount;
	T* _pPtr;
	mutex* _pMutex;
};

template<class T>
class WeakPtr
{
public://给出默认构造和拷贝构造，其中拷贝构造不能有从原始指针进行构造
	WeakPtr()
	{
		_ptr = 0;
		cnt = 0;
		cout << "WeakPtr construct " << endl;
	}
	WeakPtr(SharePtr<T>& s) :
		_ptr(s._ptr), cnt(s.cnt)
	{
		cout << "w con s" << endl;
		cnt->w++;
	}
	WeakPtr(WeakPtr<T>& w) :
		_ptr(w._ptr), cnt(w.cnt)
	{
		cnt->w++;
	}
	~WeakPtr()
	{
		release();
	}
	WeakPtr<T>& operator =(WeakPtr<T> & w)
	{
		if (this != &w)
		{
			release();
			cnt = w.cnt;
			cnt->w++;
			_ptr = w._ptr;
		}
		return *this;
	}
	WeakPtr<T>& operator =(SharePtr<T> & s)
	{
		cout << "w = s" << endl;
		release();
		cnt = s.cnt;
		cnt->w++;
		_ptr = s._ptr;
		return *this;
	}
	SharePtr<T> lock()
	{
		return SharePtr<T>(*this);
	}
	bool expired()
	{
		if (cnt)
		{
			if (cnt->s >0)
			{
				cout << "empty " << cnt->s << endl;
				return false;
			}
		}
		return true;
	}
	friend class SharePtr<T>;//方便weak_ptr与share_ptr设置引用计数和赋值。
private:
	void release()
	{
		cout << "into WeakPtr release" << endl;
		if (cnt)
		{
			cnt->w--;
			if (cnt->w <1 && cnt->s <1)
			{
				cout << "weakptr release" << endl;
				cnt = NULL;
			}
		}
	}
	T* _ptr;
	Counter* cnt;
};

