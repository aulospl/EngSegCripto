all:
	gcc -Wall -o rsa rsa.c -lm

clean:
	rm rsa out.txt

install:
	./rsa e README.md out.txt
