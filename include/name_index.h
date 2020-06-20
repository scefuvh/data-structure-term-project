/*
 * Copyright 2020 David Hu, all rights reserved.
 * Email: 1697552203@qq.com
 */


#ifndef __hhz_name_index
#define __hhz_name_index


/*
 * The NameIndex class, used to store a restaurant.
 */
struct NameIndex
{
    char name[15], cooking_style[15];
    unsigned x, y;
    bool operator<(const NameIndex &a) const;
    bool operator==(const NameIndex &a) const;
    bool operator>(const NameIndex &a) const;
    bool operator<=(const NameIndex &a) const;
    bool operator>=(const NameIndex &a) const;
    bool operator!=(const NameIndex &a) const;
};


#endif
