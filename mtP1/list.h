#ifndef __SYMLIST_H
#define __SYMLIST_H

#include "global.h"

class symList {
    private:
        unsigned int listCapacity;
        unsigned int listCount;
        symbol *symbols;
    public:
        symList(unsigned int listCapacity);
        unsigned int getCount() { return listCount; }
        voi dumpList();
};

#endif
