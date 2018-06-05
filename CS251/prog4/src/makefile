test1:	pq.o main1.o
	gcc -o test1 pq.o main1.o -g

test2:	pq.o main2.o
	gcc -o test2 pq.o main2.o -g

pq.o:	pq.c pq.h
	gcc -c pq.c

main1.o:	main1.c pq.h
		gcc -c main1.c

main2.o:	main2.c pq.h
		gcc -c main2.c

clean1:
	rm pq.o main1.o test1

clean2:
	rm pq.o main2.o test2
