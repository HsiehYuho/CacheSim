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

#define ITERATION 100
#define PARTITION 4

// Array of pre-gen address
#define ADDR_LENGTH 10

// The mode of data fetching
#define MODE 2

int main(int argc, const char * argv[]) {
    srand((unsigned int) time(NULL));
    printf("Hello world \n");
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
            printf("%d: miss rate: %.5f \n", i, get_miss_rate());
        }
    }
    printf("\n");
    
    
    /*****TEST REPEATING DATA***/
    printf("Repeating Data \n");
    int section = ITERATION / PARTITION; // 25
    printf("Section: %d \n",section);
    for(int i = 0; i < ITERATION; i++){
        int stage = i / section;
        if(stage % 2 == 0){
            simulate(0, section / itr_to_addr);
        }else{
            simulate(section / itr_to_addr , ADDR_LENGTH);
        }
        if(i % sample_rate == 0){
            printf("%d: miss rate: %.5f \n", i, get_miss_rate());
        }
    }
    printf("\n");
    

    printf("Finish! \n");
    return 0;
}
