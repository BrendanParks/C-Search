search : search.c
	gcc -g search.c -o search
test : test.c
	gcc -g test.c -o test
clean :
	rm edit search
	rm edit test
run :
	make
	./search