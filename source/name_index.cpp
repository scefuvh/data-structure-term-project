/*
 * Copyright 2020 David Hu, all rights reserved.
 * Email: 1697552203@qq.com
 */


#include "../include/name_index.h"
#include <cstring>


bool NameIndex::operator<(const NameIndex &a) const
{
    return strcmp(name, a.name) < 0;
}
bool NameIndex::operator==(const NameIndex &a) const
{
    return strcmp(name, a.name) == 0;
}
bool NameIndex::operator>(const NameIndex &a) const
{
    return strcmp(name, a.name) > 0;
}
bool NameIndex::operator<=(const NameIndex &a) const
{
    return strcmp(name, a.name) <= 0;
}
bool NameIndex::operator>=(const NameIndex &a) const
{
    return strcmp(name, a.name) >= 0;
}
bool NameIndex::operator!=(const NameIndex &a) const
{
    return strcmp(name, a.name) != 0;
}
