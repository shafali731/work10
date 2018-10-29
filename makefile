all:
	gcc -o out random.c

run:
	./a.out

clean:
	rm -rf *.out
