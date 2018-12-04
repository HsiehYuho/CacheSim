# CacheSim

CSE 6010 Final Project

-------------

Author          : Yu-Ho Hsieh, Puting Yu

Created         : Dec 4 , 2018

Last Modified   : Dec 4, 2018

Affiliation          : Georgia Institute of Technology


## Description
-------------

The project is to experiment the performance of different cache design under different use cases as well as to understand the impact of well-design cache mechanism on the speed of an program execution. The below section start with the motivation of this project, and then the implementation of different cache design, then how we test the performance and the experiment results. 

## Folder Structure
-------------



├── src       # Source files, include simulation program and lib program
    
├── Makefile

└── README.md    


## Compilation & Experiment
-------------

Please run make under *Cache_Sim* folder.
```
make
```
Then you will find the folder will have several .o files, do not worry about that, the make clean command later will clean them up. 

Then please run exe file to simulate the experiment with required parameters and file path.


Example:
```
./cache_sim
```

After running the above example command, you should be able to see the output statistics and necessary info from the terminal. 

## Change Parameter

If you want to change the parameter, please go to following files to change it
size of cache block : Cache_lib.c SIZE 
n-way assotiative : Cache_lib.c DATA_SPACE
number of instructions: main.c ADDR_LENGTH
LRU & MU : main.c MODE 
