
#ifndef __SHARED_PTR_
#define __SHARED_PTR_

template <typename T>
class shared_ptr
{
public:
    shared_ptr(T *p) : count(new int(1)), _ptr(p){};
    //拷贝构造函数
    shared_ptr(shared_ptr<T> &other) : count(&(++*other.count)), _ptr(other._ptr) {}
    //拷贝赋值
    shared_ptr<T> &operator=(shared_ptr<T> &other)
    {
        ++*(other.count);
        if (this->_ptr && 0 == --*this->count)
        {
            delete count;
            delete _ptr;
        }

        this->_ptr = other._ptr;
        this->count = other.count;
        return *this;
    }

    //移动构造 函数是这样写的吗
    shared_ptr(shared_ptr<T> &&other) : ptr(other.ptr), count(other.count)
    {
        other.ptr = nullptr;
        other.count = nullptr;
    }
    //移动赋值 函数 是这么写的吗
    shared_ptr<T> &operator=(shared_ptr<T> &&other)
    {
        if (this != &other)
        {
            this->ptr = other.ptr;
            this->count = other.count;
        }
        return *this;
    }
    
    ~shared_ptr()
    {
        if (--*count == 0)
        {
            delete count;
            delete _ptr;
        }
    }
    T *get_ptr() { return _ptr; }
    int getref() { return *count; }
    T *operator->() { return _ptr; }
    T &operator*() { return *_ptr; }

private:
    int *count; //这个count一定是指向堆区的这样才能共享
    T *_ptr;
};
template<typename>
class Weak_ptr
{
	public:
		Weak_ptr(T* ptr=NULL ):mptr(ptr){}
		Weak_ptr(const Weak_ptr<T>& rhs){
			mptr = rhs.mptr;
		}
		Weak_ptr<T> &operator=(const Weak_ptr<T>& rhs)
		{
			if (this != &rhs)
			{
				mptr = rhs.mptr
			}
			return *this;
		}
		Weak_ptr<T> &operator=(const Shared_ptr<T>& rhs)
		{
			mptr = rhs.getPtr();
			return *this;
		}
		~Weak_ptr(){};
		T* operator->()
		{
			return mptr;
		}
		T& operator *()
		{
			return *mptr;
		}
	private:
		T *mptr;
};
#endif
