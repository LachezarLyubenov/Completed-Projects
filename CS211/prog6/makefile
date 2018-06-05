
project6:	proj6Base.o myListNode.o myList.o airport.o TravelNetwork.o
								g++ -o project6 proj6Base.o myListNode.o myList.o airport.o TravelNetwork.o

proj6Base.o: proj6Base.cpp TravelNetwork.h
								g++ -c proj6Base.cpp

MyListNode.o:		myListNode.cpp myListNode.h
								g++ -c myListNode.cpp

myList.o:				myList.cpp myList.h
								g++ -c myList.cpp

airport.o:			airport.cpp airport.h
								g++ -c airport.cpp

TravelNetwork.o:	TravelNetwork.cpp TravelNetwork.h
								g++ -c TravelNetwork.cpp

clear:
								rm proj6Base.o myListNode.o myList.o airport.o TravelNetwork.o
