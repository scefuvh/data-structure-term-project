/*
 * Copyright 2020 David Hu, all rights reserved.
 * Email: 1697552203@qq.com
 */


#include<vector>


#ifndef __hhz_style_class


/*
 * The StyleIndex class, which is used to store restaurants
 * in term of their cooking stylies
 */
struct StyleIndex
{
    char name[15];
    double dis;
    int x, y;
    bool valid = false;
    bool operator> (const StyleIndex &b);
    bool operator< (const StyleIndex &b);
    bool operator>= (const StyleIndex &b);
    bool operator<= (const StyleIndex &b);
    bool operator== (const StyleIndex &b);
    bool operator!= (const StyleIndex &b);
};


/* The StyleHead class, used for storing all restaurants
 * of the same cooking style
 */
struct StyleHead
{
    std::vector<StyleIndex> style_vector;
    char cooking_style[15];
    unsigned pick_kth_nearest(int start, int afterend, unsigned k);
    void sort(int start, int afterend);
    void exchange(int a, int b);
    bool operator <(const StyleHead &a) const;
    bool operator ==(const StyleHead &a) const;
    bool operator >(const StyleHead &a) const;
    bool operator <=(const StyleHead &a) const;
    bool operator >=(const StyleHead &a) const;
    bool operator !=(const StyleHead &a) const;
    protected:
        unsigned partition(int start, int afterend, unsigned k);
};


#define __hhz_style_class
#endif
