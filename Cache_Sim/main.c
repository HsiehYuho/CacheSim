//
//  main.c
//  Cache_Sim
//
//  Created by Hsieh Yuho on 2018/11/18.
//  Copyright © 2018 Yu-Ho Hsieh. All rights reserved.
//

#include <stdio.h>
#include "sim.h"
#include <time.h>
#include <stdlib.h>

#define ITERATION 1000
#define PARTITION 10

// Array of pre-gen address
#define ADDR_LENGTH 100

// The mode of data fetching, 1 : count dominate, 2 : time dominate
#define MODE 1

int main(int argc, const char * argv[]) {
    srand((unsigned int) time(NULL));
    // Consts
    int sample_rate = (ITERATION / 10);
    int itr_to_addr = ITERATION / ADDR_LENGTH;
    
    init(ADDR_LENGTH, MODE);
    if(MODE == 1){
        printf("Count dominate \n");
    }

    if(MODE == 2){
        printf("Time dominate \n");
    }

    /*****TEST KEEP_MOVING DATA***/
    int portion = ITERATION/PARTITION; // 250
    printf("Portion: %d \n",portion);
    printf("Keep Moving Data \n");
    for(int i = 0; i < ITERATION; i++){
        int stage = i / portion; // 1 , 2 , 3 , 4 stage
        simulate(stage * portion / itr_to_addr, (stage+1) * portion / itr_to_addr);
        if((i % sample_rate) == 0){
//            printf("\n %d: miss rate: %.5f \n", i, get_miss_rate());
            printf("%.5f \n",get_miss_rate());

        }
    }
    printf("\n");
    clear_cache();

    init(ADDR_LENGTH, MODE);
    /*****TEST REPEATING DATA***/
    printf("Repeating Data \n");
    int section = ITERATION / PARTITION; // 25
    printf("Section: %d \n",section);
    for(int i = 0; i < ITERATION; i++){
        int stage = i / section;
        if(stage % 10 == 0){
            simulate(section / itr_to_addr , ADDR_LENGTH);
        }else{
            simulate(0, section / itr_to_addr);
        }
        if(i % sample_rate == 0){
//            printf("\n %d: miss rate: %.5f \n", i, get_miss_rate());
            printf("%.5f \n",get_miss_rate());
        }
    }
    free_gen_array(ADDR_LENGTH);
    clear_cache();
    printf("\n");
    printf("Finish! \n");
    return 0;
}
