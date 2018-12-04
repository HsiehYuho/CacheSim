output: sim.o Cache_lib.o main.o
	gcc -std=c99 sim.o Cache_lib.o main.o -o cache_sim 

main.o: ./src/main.c ./src/sim.h
	gcc -std=c99 -c ./src/main.c

sim.o: ./src/sim.h ./src/sim.c
	gcc -std=c99 -c ./src/sim.c

Cache_lib.o: ./src/Cache_lib.h ./src/Cache_lib.c
	gcc -std=c99 -c ./src/Cache_lib.c

clean: 
	rm *.o cache_sim

