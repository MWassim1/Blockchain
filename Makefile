CC=gcc
CFLAGS=-Wall
LDFLAGS=-lssl -lcrypto

ex1=Partie1/Exercice1
ex2=Partie1/Exercice2
ex3=Partie2/Exercice3
ex4=Partie2/Exercice4
ex5=Partie3/Exercice5
ex6=Partie4/Exercice6
ex7=Partie5/Exercice7
ex8=Partie5/Exercice8
ex9=Partie5/Exercice9

all: main_ex1 main_ex2 main_ex3 main_ex4 main_ex5 main_ex6 main_ex7 main_ex8 main_ex9

exercice1.o: $(ex1)/exercice1.c
	$(CC) $(CFLAGS) -o $(ex1)/exercice1.o -c $<

exercice2.o: $(ex2)/exercice2.c
	$(CC) $(CFLAGS) -o $(ex2)/exercice2.o -c $<

exercice3.o: $(ex3)/exercice3.c
	$(CC) $(CFLAGS) -o $(ex3)/exercice3.o -c $<

exercice4.o: $(ex4)/exercice4.c
	$(CC) $(CFLAGS) -o $(ex4)/exercice4.o -c $<

exercice5.o: $(ex5)/exercice5.c
	$(CC) $(CFLAGS) -o $(ex5)/exercice5.o -c $<

exercice6.o: $(ex6)/exercice6.c
	$(CC) $(CFLAGS) -o $(ex6)/exercice6.o -c $<

exercice7.o: $(ex7)/exercice7.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(ex7)/exercice7.o -c $<

exercice8.o: $(ex8)/exercice8.c
	$(CC) $(CFLAGS) -o $(ex8)/exercice8.o -c $<

exercice9.o: $(ex9)/exercice9.c
	$(CC) $(CFLAGS) -o $(ex9)/exercice9.o -c $<

main_ex1.o: $(ex1)/main.c $(ex1)/exercice1.h
	$(CC) $(CFLAGS) -o $(ex1)/main_ex1.o -c $<

main_ex2.o: $(ex2)/main.c $(ex1)/exercice1.h $(ex2)/exercice2.h
	$(CC) $(CFLAGS) -o $(ex2)/main_ex2.o -c $<

main_ex3.o: $(ex3)/main.c $(ex1)/exercice1.h $(ex2)/exercice2.h $(ex3)/exercice3.h
	$(CC) $(CFLAGS) -o $(ex3)/main_ex3.o -c $<

main_ex4.o: $(ex4)/main.c $(ex1)/exercice1.h $(ex2)/exercice2.h $(ex3)/exercice3.h $(ex4)/exercice4.h
	$(CC) $(CFLAGS) -o $(ex4)/main_ex4.o -c $<

main_ex5.o: $(ex5)/main.c $(ex1)/exercice1.h $(ex2)/exercice2.h $(ex3)/exercice3.h $(ex4)/exercice4.h $(ex5)/exercice5.h
	$(CC) $(CFLAGS) -o $(ex5)/main_ex5.o -c $<

main_ex6.o: $(ex6)/main.c $(ex1)/exercice1.h $(ex2)/exercice2.h $(ex3)/exercice3.h $(ex4)/exercice4.h $(ex5)/exercice5.h $(ex6)/exercice6.h
	$(CC) $(CFLAGS) -o $(ex6)/main_ex6.o -c $<

main_ex7.o: $(ex7)/main.c $(ex1)/exercice1.h $(ex2)/exercice2.h $(ex3)/exercice3.h $(ex4)/exercice4.h $(ex5)/exercice5.h $(ex6)/exercice6.h $(ex7)/exercice7.h
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(ex7)/main_ex7.o -c $<

main_ex8.o: $(ex8)/main.c $(ex1)/exercice1.h $(ex2)/exercice2.h $(ex3)/exercice3.h $(ex4)/exercice4.h $(ex5)/exercice5.h $(ex6)/exercice6.h $(ex7)/exercice7.h $(ex8)/exercice8.h
	$(CC) $(CFLAGS) -o $(ex8)/main_ex8.o -c $<

main_ex9.o: $(ex9)/main.c $(ex1)/exercice1.h $(ex2)/exercice2.h $(ex3)/exercice3.h $(ex4)/exercice4.h $(ex5)/exercice5.h $(ex6)/exercice6.h $(ex7)/exercice7.h $(ex8)/exercice8.h $(ex9)/exercice9.h
	$(CC) $(CFLAGS) -o $(ex9)/main_ex9.o -c $<

main_ex1: main_ex1.o exercice1.o
	$(CC) $(CFLAGS) -o $(ex1)/main $(ex1)/main_ex1.o $(ex1)/exercice1.o

main_ex2: main_ex2.o exercice1.o exercice2.o
	$(CC) $(CFLAGS) -o $(ex2)/main $(ex2)/main_ex2.o $(ex1)/exercice1.o $(ex2)/exercice2.o

main_ex3: main_ex3.o exercice1.o exercice2.o exercice3.o
	$(CC) $(CFLAGS) -o $(ex3)/main $(ex3)/main_ex3.o $(ex1)/exercice1.o $(ex2)/exercice2.o $(ex3)/exercice3.o

main_ex4: main_ex4.o exercice1.o exercice2.o exercice3.o exercice4.o
	$(CC) $(CFLAGS) -o $(ex4)/main $(ex4)/main_ex4.o $(ex1)/exercice1.o $(ex2)/exercice2.o $(ex3)/exercice3.o $(ex4)/exercice4.o

main_ex5: main_ex5.o exercice1.o exercice2.o exercice3.o exercice4.o exercice5.o
	$(CC) $(CFLAGS) -o $(ex5)/main $(ex5)/main_ex5.o $(ex1)/exercice1.o $(ex2)/exercice2.o $(ex3)/exercice3.o $(ex4)/exercice4.o $(ex5)/exercice5.o

main_ex6: main_ex6.o exercice1.o exercice2.o exercice3.o exercice4.o exercice5.o exercice6.o
	$(CC) $(CFLAGS) -o $(ex6)/main $(ex6)/main_ex6.o $(ex1)/exercice1.o $(ex2)/exercice2.o $(ex3)/exercice3.o $(ex4)/exercice4.o $(ex5)/exercice5.o $(ex6)/exercice6.o

main_ex7: main_ex7.o exercice1.o exercice2.o exercice3.o exercice4.o exercice5.o exercice6.o exercice7.o
	$(CC) $(CFLAGS) -o $(ex7)/main $(ex7)/main_ex7.o $(ex1)/exercice1.o $(ex2)/exercice2.o $(ex3)/exercice3.o $(ex4)/exercice4.o $(ex5)/exercice5.o $(ex6)/exercice6.o $(ex7)/exercice7.o $(LDFLAGS)

main_ex8: main_ex8.o exercice1.o exercice2.o exercice3.o exercice4.o exercice5.o exercice6.o exercice7.o exercice8.o
	$(CC) $(CFLAGS) -o $(ex8)/main $(ex8)/main_ex8.o $(ex1)/exercice1.o $(ex2)/exercice2.o $(ex3)/exercice3.o $(ex4)/exercice4.o $(ex5)/exercice5.o $(ex6)/exercice6.o $(ex7)/exercice7.o $(ex8)/exercice8.o $(LDFLAGS)

main_ex9: main_ex9.o exercice1.o exercice2.o exercice3.o exercice4.o exercice5.o exercice6.o exercice7.o exercice8.o exercice9.o
	$(CC) $(CFLAGS) -o $(ex9)/main $(ex9)/main_ex9.o $(ex1)/exercice1.o $(ex2)/exercice2.o $(ex3)/exercice3.o $(ex4)/exercice4.o $(ex5)/exercice5.o $(ex6)/exercice6.o $(ex7)/exercice7.o $(ex8)/exercice8.o $(ex9)/exercice9.o $(LDFLAGS)
clean:
	rm -f */*/*.o */*/main

