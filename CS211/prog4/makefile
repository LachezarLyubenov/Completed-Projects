restaurantMain.o: restaurantMain.c restaurant.h
		gcc -c restaurantMain.c

mainFunctions.o: mainFunctions.c restaurant.h
		gcc -c mainFunctions.c

linkedListImplement.o: linkedListImplement.c restaurant.h
		gcc -c linkedListImplement.c

all: restaurantMain.o mainFunctions.o linkedListImplement.o
		gcc restaurantMain.o mainFunctions.o linkedListImplement.o -o rest

clean:
		  	$(RM) rest *.o *~
