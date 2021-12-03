#ifndef __STL_MAP_H
#define __STL_MAP_H

template <class Key, class T, class Compare = less<Key>, class Alloc = alloc>
class map
{
    typedef Key key_type;
    typedef T data_type;
    typedef T mapped_type;
    typedef pair<const Key, T> value_type;
    typedef Compare key_compare;
    class value_compare : public binary_function<value_type, value_type, bool>
    {
        friend class map<Key, T, Compare, Alloc>;

    protected:
        Compare comp;
        value_compare(Compare c) : comp(c) {}

    public:
        bool opeator()(const value_type &x, const value_type &y) const
        {
            return comp(x.first, y.first);
        }
    }
};

#endif