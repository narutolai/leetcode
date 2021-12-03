#ifndef __STL_MAP_H
#define __STL_MAP_H
#include "stl_RB_tree.h"
template <class Key, class Compare = less<Key>, class Alloc = alloc>
class set
{
    typedef Key key_type;
    typedef Key value_type;

    //key_compare和value_compare使用同一个比较函数
    typedef Compare key_compare;
    typedef Compare value_compare;

private:
    template <class T>
    struct identity : public unary_function<T, T>
    {
        const T &operator()(const T &x) const { return x; }
    };
    typedef rb_tree<key_type, value_type, identity<value_type>, key_compare, Alloc> rep_type;
    rep_type t; //才有红黑树 来表现 set
public:
    typedef typename rep_type::const_pointer pointer;
    typedef typename rep_type::const_pointer const_pointer;
    typedef typename rep_type::const_reference reference;
    typedef typename rep_type::const_reference const_reference;
    typedef typename rep_type::const_iterator iterator;
    //注意set的迭代器是无法执行任意写操作的m，这是因为set的元素一定是有次序安排的。
    typedef typename rep_type::const_iterator const_iterator;
    typedef typename rep_type::const_reverse_iterator reverse_iterator;
    typedef typename rep_type::const_reverse_iterator const_reverse_iterator;
    typedef typename rep_type::size_type size_type;
    typedef typename rep_type::difference_type difference_type;

    set() : t(Compare()) {}
    explicit set(const Compare &comp) : t(comp) {}

    template <class InputIterator>
    set(InputIterator first, InputIterator last) : t(Compare()) { t.insert_unique(first, last); }

    set(const set<Key, Compare, Alloc> &x) : t(x.t) {}
    set<Key, Comparea, Alloc> &operator=(const set<Key, Compare, Alloc> &x)
    {
        t = x.t;
        return *this;
    }
    //以下的所有set的操作行为 RB-TREE已经提供 所以set只需要传递调用就可以
    //accessor
    key_compare key_comp() const { return t.key_comp(); }
    value_compare value_comp() const { return t.key_comp(); }
    iterator begin() const { return t.begin(); }
    iterator end() const { return t.end(); }
    reverse_iterator rbegin() const { return t.rbegin(); }
    reverse_iterator rend() const { return t.rend(); }
    bool empty() const { return t.empty(); }

    size_type size() const { return t.size(); }
    size_type max_size() const { return t.max_size(); }
    void swap(set<Key, Compare, Alloc> &x) { t.swap(x.t); }

    //insert/erase
    typedef pair<iterator, bool> pair_iterator_bool;
    pair<iterator, bool> insert(const value_type &x)
    {
        pair<typename rep_type::iterator, bool> p = t.insert_unique(x);
        return pair<iterator, bool>(p.first, p.second);
    }

    void erase(iterator position)
    {
        typedef typename rep_type::iterator rep_iterator;
        t.erase((rep_iterator &)position);
    }

    size_type erase(const key_type &x)
    {
        return t.erase(x);
    }
    void erase(iterator first, iterator last)
    {
        typedef typename rep_type::iterator rep_iterator;
        t.erase((rep_iterator &)first, (rep_iterator &)last);
    }
    void clear() { t.clear(); }
    //.......
};

#endif