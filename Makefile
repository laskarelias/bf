compile:
	cc -Wall -o bf bf.c

clean:
	rm -rf bf

run:
	./bf input.bf
	
debug:
	cc -Wall -g -o bf bf.c
	gdb --args ./bf input.bf
