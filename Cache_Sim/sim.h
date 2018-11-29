//
//  sim.h
//  Cache_Sim
//
//  Created by Hsieh Yuho on 2018/11/18.
//  Copyright © 2018 Yu-Ho Hsieh. All rights reserved.
//

#ifndef sim_h
#define sim_h

#include <stdio.h>
#include <stdbool.h>
#include "Cache_lib.h"

#endif /* sim_h */

/*
 * Init the whole simulate process
 * @param: void
 * @return: void
 */
void init(int addr_length, Mode mode);

/*
 * Simulate 1 iteration
 * @param: the start of idx and the end of index
 * @return: bool, true if simulate success, else false 
 */
bool simulate(int range_start, int range_end);

/*
 * Call cache miss rate api to cacluate statistics
 * @param: none
 * @return: miss rate in percentage
 */
double get_miss_rate(void);

/*
 * Free the gen array ptr
 * @param: the length of gen array 
 * @return: none
 */
void free_gen_array(int addr_length);

