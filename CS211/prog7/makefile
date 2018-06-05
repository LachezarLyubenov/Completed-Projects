compiler = g++
Flags = -g -std=c++11 -Wall

proj7:  		Creature.o Ant.o Doodlebug.o GridDisplay.o llyube2proj7.o
				$(compiler) $(Flags) -o proj7 Creature.o Ant.o Doodlebug.o GridDisplay.o llyube2proj7.o 

llyube2proj7.o: llyube2proj7.cpp
				$(compiler) $(Flags) -c llyube2proj7.cpp

Creature.o: 	Creature.cpp Creature.h
				$(compiler) $(Flags) -c Creature.cpp

Ant.o:			Ant.cpp Ant.h
				$(compiler) $(Flags) -c Ant.cpp

Doodlebug.o:	Doodlebug.cpp Doodlebug.h
				$(compiler) $(Flags) -c Doodlebug.cpp

GridDisplay.o:	GridDisplay.cpp GridDisplay.h
				$(compiler) $(Flags) -c GridDisplay.cpp

clean:
				rm -f *.o proj7
