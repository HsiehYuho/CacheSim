//
//  sim.c
//  Cache_Sim
//
//  Created by Hsieh Yuho on 2018/11/18.
//  Copyright © 2018 Yu-Ho Hsieh. All rights reserved.
//

#include "sim.h"
#include <stdlib.h>
#include "Cache_lib.h"

// Restful
#define READ_PERCENT 0.5
#define UPDATE_PERCENT (1-READ_PERCENT)

#define READ 0
#define UPDATE 1

typedef int COMMAND;

/*
 * Functions in simulation
 */

// Functions in init
int** gen_array_of_addr(int length);

// Functions in simulation
COMMAND gen_command(void);
int gen_idx(int range_start, int range_end);
int gen_data(void);

// Global variables
static int** array_ptr = NULL;

void init(int addr_length, Mode mode){
    array_ptr = gen_array_of_addr(addr_length);
    Init(mode);
    for(int i = 0; i < addr_length; i++){
        cache_write(array_ptr[i],*(array_ptr[i]));
    }
}

bool simulate(int range_start, int range_end){
    COMMAND command = gen_command();
    if(command == READ){
        int idx = gen_idx(range_start, range_end);
        int* ptr = array_ptr[idx];
        int data = cache_read(ptr);
        if(data != *ptr){
            printf("Data inconsistent \n");
            return false;
        }
        return true;
    }
    else if (command == UPDATE){
        int idx = gen_idx(range_start, range_end);
        int* ptr = array_ptr[idx];
        *ptr = gen_data();
        cache_write(ptr, *ptr);
        return true;
    }
    else{
        return false;
    }
    return false;
}

double get_miss_rate(){
    return cache_get_miss_rate();
}

/**********HELPER FUNCTIONS******************/

// We can have another malloc, we malloc a whole array to address spatial locality

// Temporal locality (Current way)
int** gen_array_of_addr(int length){
    int** ptr = malloc(sizeof(int*) * length);
    for(int i = 0; i < length; i++){
        ptr[i] = malloc(sizeof(int));
        *(ptr[i]) = gen_data();
    }
    return ptr;
}

int gen_data(){
    return (rand() % 1000);
}

int gen_idx(int range_start, int range_end){
    int idx = rand() % (range_end - range_start);
    return idx + range_start;
}

COMMAND gen_command(void){
    double command = (rand() % 1001) / 1000.0;
    if(command < READ_PERCENT)
        return READ;
    else
        return UPDATE;
}
