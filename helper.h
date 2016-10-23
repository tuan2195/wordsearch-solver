//
//  helper.h
//  Project3a
//
//  Created by Tuan Dao on 10/9/15.
//  Copyright (c) 2015 Tuan Dao. All rights reserved.
//

#ifndef Project3a_helper_h
#define Project3a_helper_h

#include <algorithm>

void undefinedBehavior(void)
{
    std::cout << "Undefined behavior! Check your input!\n";
    exit(-1);
}

int posMod(int x, int mod)
{
    int ret = x%mod;
    if (ret < 0)
        return mod+ret;
    else
        return ret;
}


#endif
