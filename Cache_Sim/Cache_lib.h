//
//  Cache_lib.h
//  Final_Project_6010
//
//  Created by 游步庭 on 2018/11/18.
//  Copyright © 2018 游步庭. All rights reserved.
//

#ifndef Cache_lib_h
#define Cache_lib_h
#include <stdio.h>
#include <stdlib.h>
typedef int Mode;
void Init(Mode mode);
void cache_write(int* address, int data);
int  cache_read(int* address);
double cache_get_miss_rate(void);
void clear_cache(void);
#endif /* Cache_lib_h */
