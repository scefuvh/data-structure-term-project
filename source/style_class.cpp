/*
 * Copyright 2020 David Hu, all rights reserved.
 * Email: 1697552203@qq.com
 */


#include<cstring>
#include<ctime>
#include<cstdlib>
#include<vector>
#include "../include/style_class.h"


/*
 * The implementations of comparison methods in StyleIndex
 */
bool StyleIndex::operator > (const StyleIndex &b)
{
    if(dis != b.dis)
        return dis > b.dis;
    return strcmp(name, b.name) > 0;
}

bool StyleIndex::operator < (const StyleIndex &b)
{
    if(dis != b.dis)
        return dis < b.dis;
    return strcmp(name, b.name) < 0;
}

bool StyleIndex::operator <= (const StyleIndex &b)
{
    if(dis != b.dis)
        return dis <= b.dis;
    return strcmp(name, b.name) <= 0;
}

bool StyleIndex::operator >= (const StyleIndex &b)
{
    if(dis != b.dis)
        return dis >= b.dis;
    return strcmp(name, b.name) >= 0;
}

bool StyleIndex::operator != (const StyleIndex &b)
{
    if(dis != b.dis)
        return true;
    return strcmp(name, b.name) != 0;
}

bool StyleIndex::operator == (const StyleIndex &b)
{
    if(dis != b.dis)
        return false;
    return strcmp(name, b.name) == 0;
}


/*
 * The implementations of non-comparison methonds of StyleHead class
 */
void StyleHead::exchange(int a, int b)
{
    StyleIndex tmp = style_vector[a];
    style_vector[a] = style_vector[b];
    style_vector[b] = tmp;
    return;
}

void StyleHead::sort(int start, int afterend)
{
    while(afterend - start > 2)
    {

        // Take the median as pivot
        int mid = start +  (afterend - start) / 2;
        if(style_vector[afterend-1] < style_vector[start])
            exchange(afterend-1, start);
        if(style_vector[afterend-1] < style_vector[mid])
            exchange(mid, afterend-1);
        if(style_vector[start] < style_vector[mid])
            exchange(start, mid);
        StyleIndex pivot = style_vector[start];

        // Start partitioning
        int i = start + 1, j = afterend - 1;
        while(true)
        {
            while(style_vector[i] < pivot)
                ++i;
            --j;
            while(pivot < style_vector[j])
                --j;
            if(i >= j) break;
            exchange(i, j);
            ++i;
        }
        sort(i, afterend);
        if(afterend == i) return;
        afterend = i;
    }

    // Final sort.
    if(style_vector[afterend - 1] < style_vector[start])
        exchange(afterend-1, start);
    return;
}


unsigned StyleHead::pick_kth_nearest(int start, int afterend, unsigned k)
{
    srand(time(NULL));
    while(start < afterend)
    {
        // Choose a pivot
        unsigned pivot_index = rand() % (afterend - start) + start;
        pivot_index = partition(start, afterend, pivot_index);

        // Narrowing down
        if(k == pivot_index)
            return k;
        else if(k < pivot_index)
            afterend = pivot_index;
        else
            start = pivot_index + 1;
    }
    return start;
}


unsigned StyleHead::partition(int start, int afterend, unsigned k)
{
    // Partitioning according to the given pivot.
    StyleIndex pivot = style_vector[k];
    style_vector[k] = style_vector[afterend - 1];
    style_vector[afterend - 1] = pivot;

    unsigned store_index = start;
    for(int i = start; i < afterend - 1; i++)
        if(style_vector[i] < pivot)
        {
            StyleIndex temp = style_vector[i];
            style_vector[i] = style_vector[store_index];
            style_vector[store_index] = temp;
            store_index++;
        }

    StyleIndex temp = style_vector[afterend-1];
    style_vector[afterend-1] = style_vector[store_index];
    style_vector[store_index] = temp;

    return store_index;
}


/*
 * The implementations of comparison methods in StyleHead
 */
bool StyleHead::operator<(const StyleHead &a) const
{
    return strcmp(cooking_style, a.cooking_style) < 0;
}
bool StyleHead::operator==(const StyleHead &a) const
{
    return strcmp(cooking_style, a.cooking_style) == 0;
}
bool StyleHead::operator>(const StyleHead &a) const
{
    return strcmp(cooking_style, a.cooking_style) > 0;
}
bool StyleHead::operator<=(const StyleHead &a) const
{
    return strcmp(cooking_style, a.cooking_style) <= 0;
}
bool StyleHead::operator>=(const StyleHead &a) const
{
    return strcmp(cooking_style, a.cooking_style) >= 0;
}
bool StyleHead::operator!=(const StyleHead &a) const
{
    return strcmp(cooking_style, a.cooking_style) != 0;
}
