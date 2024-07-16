parametrosCompilacao=-Wall #-Wshadow
trab12024450=trab

all: $(trab12024450)

$(trab12024450): main.o ordenacao.o
	gcc -o $(trab12024450) main.o ordenacao.o $(parametrosCompilacao)

main.o: main.c
	gcc -c main.c $(parametrosCompilacao)

ordenacao.o: ordenacao.h ordenacao.c
	gcc -c ordenacao.c $(parametrosCompilacao)

clean:
	rm -f *.o *.gch $(trab12024450)
