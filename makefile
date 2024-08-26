all: trabalho2

trabalho2: trabalho2.o estoque.o leitura.o
	gcc -Wall -o trabalho2 build/trabalho2.o build/estoque.o build/leitura.o

trabalho2.o: trabalho2.c
	gcc -c -Wall trabalho2.c
	mkdir -p build
	mv trabalho2.o build

estoque.o: estoque.c 
	gcc -c -Wall estoque.c
	mkdir -p build
	mv estoque.o build

leitura.o: leitura.c 
	gcc -c -Wall leitura.c
	mkdir -p build
	mv leitura.o build

clean:
	rm -rf build
	rm trabalho2