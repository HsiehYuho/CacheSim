//
//  Cache_lib.c
//  Final_Project_6010
//
//  Created by 游步庭 on 2018/11/18.
//  Copyright © 2018 游步庭. All rights reserved.
//

//mode1:time stamp, first-in-first-out ; mode2: count, smaller count smaller priority.

#define SIZE 7
#define DATA_SPACE 2
typedef struct data_of_cache
{
    int occupied_or_not;
    int data;
    int priority;
    
}Cache_data;
typedef struct flag_bits
{
    int flag_bit;
    Cache_data* Space_for_data;
}First_col_cache;
static First_col_cache* Cache;// First col:flag bit, Second col: address, third col:data, fourth:priority;
static int Hit=0;
static int Miss=0;
static int Mode_signal;
static int data_count_cache[SIZE];
int* Replacement_cache(int* address);
void Priority_update(int corresponding_index, int position);//time_stamp mode
int Find_data_cache(int corresponding_index,int data);
int Find_empty_space(int corresponding_index);
int Find_lowest_priority(int corresponding_index);
#include "Cache_lib.h"
#include <limits.h>
#include <ctype.h>

void Init(Mode mode)
{
    if(mode!= 1 && mode!=2)
      {
        printf("Error: Only two modes allowed\n");
        return ;
      }
    
    Mode_signal=mode;
   
    if(!(Cache=malloc(SIZE*sizeof(First_col_cache))))
       {
           printf("Error: Malloc failure\n");
           return;
       }
    
    for(int i=0;i<SIZE;++i)
       if(!(Cache[i].Space_for_data=calloc(DATA_SPACE,sizeof(Cache_data))))
       {
           printf("Error: Malloc failure\n");
           return;
       }
    for(int i=0;i<SIZE;++i)
        for(int j=0;j<DATA_SPACE;++j)
            Cache[i].Space_for_data[j].data=INT_MIN;

}
void clear_cache(void)
{
    for(int i=0;i<SIZE;++i)
        free(Cache[i].Space_for_data);
    
    free(Cache);
    
    Hit=0;
    Miss=0;
}


double cache_get_miss_rate(void)
{
    double miss_rate = (double)Miss/(Hit+Miss);
    return miss_rate;
   
}

int Find_data_cache(int corresponding_index,int data)
{
    for(int i=0;i<DATA_SPACE;++i)
       if(Cache[corresponding_index].Space_for_data[i].data==data)
           return i;
    
    return -1;
}

int Find_lowest_priority(int corresponding_index)
{
    int lowest_priority=INT_MAX;
    int position=0;
    for(int i=0;i<DATA_SPACE;++i)
        if(Cache[corresponding_index].Space_for_data[i].priority<lowest_priority)
        {
          lowest_priority=Cache[corresponding_index].Space_for_data[i].priority;
            position=i;
        }
    return position;
}

int Find_empty_space(int corresponding_index)
{
    for(int i=0;i<DATA_SPACE;++i)
        if(Cache[corresponding_index].Space_for_data[i].occupied_or_not==0)
            return i;
    
    return -1;
}

void Priority_update(int corresponding_index, int position)
{
    int largest_priority=INT_MIN;
    for(int i=0;i<DATA_SPACE;++i)
        if(Cache[corresponding_index].Space_for_data[i].priority>largest_priority)
            largest_priority=Cache[corresponding_index].Space_for_data[i].priority;
    
    Cache[corresponding_index].Space_for_data[position].priority=largest_priority+1;
    
    for(int i=0;i<DATA_SPACE;++i)
        if(Cache[corresponding_index].Space_for_data[i].occupied_or_not==1)
           Cache[corresponding_index].Space_for_data[i].priority--;
}

void cache_write(int* address, int data)//mode1:count, mode2: time
{
    int corresponding_index=0;
    int address_to_int= (int) address;
    corresponding_index=abs(address_to_int%SIZE);
   
    if(Mode_signal==1)//count more, higher priority
     {
         if(Cache[corresponding_index].flag_bit==1)//corresponding set is full
         {
             int in_cache_or_not=Find_data_cache(corresponding_index, data);
             if(in_cache_or_not!=(-1))//data already in cache;
               {
                   Hit++;
                 Cache[corresponding_index].Space_for_data[in_cache_or_not].priority++;
               }
             else
               {
                   Miss++;
                   int lowest_priority=Find_lowest_priority(corresponding_index);
                   Cache[corresponding_index].Space_for_data[lowest_priority].data=data;
                   Cache[corresponding_index].Space_for_data[lowest_priority].priority=1;
               }
         }
         
         else
         {
             int in_cache_or_not=Find_data_cache(corresponding_index, data);
             if(in_cache_or_not==(-1))
              {
                  Miss++;
                  int empty_space=Find_empty_space(corresponding_index);
                  Cache[corresponding_index].Space_for_data[empty_space].data=data;
                  Cache[corresponding_index].Space_for_data[empty_space].priority=1;
                  Cache[corresponding_index].Space_for_data[empty_space].occupied_or_not=1;
                  data_count_cache[corresponding_index]++;
                  if(data_count_cache[corresponding_index]==DATA_SPACE)
                      Cache[corresponding_index].flag_bit=1;
                  
              }
             
             else
               {
                   Cache[corresponding_index].Space_for_data[in_cache_or_not].priority++;
                   Hit++;
               }
          }
        }
    
     if(Mode_signal==2)//last-in-first-out
     {
         if(Cache[corresponding_index].flag_bit==1)//corresponding set is full
         {
             int in_cache_or_not=Find_data_cache(corresponding_index, data);
             if(in_cache_or_not!=(-1))//data already in cache;
              {
                 Priority_update(corresponding_index,in_cache_or_not);
                 Hit++;
              }
             
             else
             {
                 Miss++;
                 int lowest_priority=Find_lowest_priority(corresponding_index);
                 Cache[corresponding_index].Space_for_data[lowest_priority].data=data;
                 Priority_update(corresponding_index,lowest_priority);
             }
         }
         
         else
         {
             int in_cache_or_not=Find_data_cache(corresponding_index, data);
             if(in_cache_or_not==(-1))
             {
                 Miss++;
                 int empty_space=Find_empty_space(corresponding_index);
                 Cache[corresponding_index].Space_for_data[empty_space].data=data;
                 Priority_update(corresponding_index, empty_space);
                 data_count_cache[corresponding_index]++;
                 if(data_count_cache[corresponding_index]==DATA_SPACE)
                     Cache[corresponding_index].flag_bit=1;
                 
             }
             else
             {
                 Hit++;
                 Priority_update(corresponding_index, in_cache_or_not);
             }
         }
     }

    return;
}

int cache_read(int* address)
{
    int corresponding_index=0;
    int address_to_int= (int) address;
    int data= (int)address;
    corresponding_index=abs(address_to_int%SIZE);
    
    if(Mode_signal==1)//count more, priority higher
    {
        if(Cache[corresponding_index].flag_bit==1)//corresponding set is full
        {
            int in_cache_or_not=Find_data_cache(corresponding_index, data);
            if(in_cache_or_not!=(-1))//data already in cache;
            {
                Hit++;
                Cache[corresponding_index].Space_for_data[in_cache_or_not].priority++;
            }
            else
            {
                Miss++;
                int lowest_priority=Find_lowest_priority(corresponding_index);
                Cache[corresponding_index].Space_for_data[lowest_priority].data=data;
                Cache[corresponding_index].Space_for_data[lowest_priority].priority=1;
            }
        }
        
        else
        {
            int in_cache_or_not=Find_data_cache(corresponding_index, data);
            if(in_cache_or_not==(-1))
            {
                Miss++;
                int empty_space=Find_empty_space(corresponding_index);
                Cache[corresponding_index].Space_for_data[empty_space].data=data;
                Cache[corresponding_index].Space_for_data[empty_space].priority=1;
                Cache[corresponding_index].Space_for_data[empty_space].occupied_or_not=1;
                data_count_cache[corresponding_index]++;
                if(data_count_cache[corresponding_index]==DATA_SPACE)
                    Cache[corresponding_index].flag_bit=1;
                
            }
            
            else
            {
                Cache[corresponding_index].Space_for_data[in_cache_or_not].priority++;
                Hit++;
            }
        }
    }
    
    if(Mode_signal==2)//last-in-first-out
    {
        if(Cache[corresponding_index].flag_bit==1)//corresponding set is full
        {
            int in_cache_or_not=Find_data_cache(corresponding_index, data);
            if(in_cache_or_not!=(-1))//data already in cache;
            {
                Priority_update(corresponding_index,in_cache_or_not);
                Hit++;
            }
            
            else
            {
                Miss++;
                int lowest_priority=Find_lowest_priority(corresponding_index);
                Cache[corresponding_index].Space_for_data[lowest_priority].data=data;
                Priority_update(corresponding_index,lowest_priority);
            }
        }
        
        else
        {
            int in_cache_or_not=Find_data_cache(corresponding_index, data);
            if(in_cache_or_not==(-1))
            {
                Miss++;
                int empty_space=Find_empty_space(corresponding_index);
                Cache[corresponding_index].Space_for_data[empty_space].data=data;
                Priority_update(corresponding_index, empty_space);
                data_count_cache[corresponding_index]++;
                if(data_count_cache[corresponding_index]==DATA_SPACE)
                    Cache[corresponding_index].flag_bit=1;
                
            }
            else
            {
                Hit++;
                Priority_update(corresponding_index, in_cache_or_not);
            }
        }
    }
    return data;
}
