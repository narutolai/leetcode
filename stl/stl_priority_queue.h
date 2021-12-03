
#include "stl_vec.h"

//heap算法--push_heap()
template <class RandomAccessIterator>
inline void push_heap(RandomAccessIterator first, RandomAccessIterator last)
{
    __push_heap_aux(first, last, distance_type(first), value_type(first));
}
template <class RandomAccessIterator, class Distance, class T>
inline void __push_heap_aux(RandomAccessIterator first, RandomAccessIterator last, Distance *, T *)
{
    __push_heap(first, Distance(last - first - 1), Distance(0), T(*(last - 1)));
}

template <class RandomAccessIterator, class Distance, class T>
void __push_heap(RandomAccessIterator first, Distance holeIndex, Distance topIndex, T value)
{
    Distance parent = (holeIndex - 1) / 2; //找到父节点
    while (holeIndex > topIndex && *(first + parent) < value)
    {
        *(first + holeIndex) = *(first + parent);
        holeIndex = parent;
        parent = (holeIndex - 1) / 2; //新洞的父节点
    }
    *(first + holeIndex) = value;
}

template <class T,
          class Sequence = vector<T>,
          class Compare = less<typename Sequence::value_type>>
class priority_queue
{
};