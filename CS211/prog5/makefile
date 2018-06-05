proj5: proj5Main.o proj5Tokens.o myStackk.o
	g++ -o proj5 proj5Main.o proj5Tokens.o myStackk.o

proj5Main.o: proj5Main.cpp proj5Tokens.h
	g++ -c proj5Main.cpp

proj5Tokens.o: proj5Tokens.cpp proj5Tokens.h
	g++ -c proj5Tokens.cpp

myStackk.o: myStackk.cpp myStack.h
	g++ -c myStackk.cpp

clean:
	rm proj5 proj5Main.o proj5Tokens.o myStackk.o
