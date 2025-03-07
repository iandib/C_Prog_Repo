# compilador:
CC = gcc

# nombre del ejecutable:
TARGET = fizzbuzz

# compila el programa:
$(TARGET): fizzbuzz.o main.o
	$(CC) -Wall -o $(TARGET) fizzbuzz.o main.o
    
# compila el test:
test: fizzbuzz.o test_fizzbuzz.o
	$(CC) -Wall -o test fizzbuzz.o test_fizzbuzz.o
    
# compila todo:
all: $(TARGET) test

# limpia el area de trabajo:
clean:
	rm *.o
    
# dependencias:
fizzbuzz.o: fizzbuzz.c fizzbuzz.h
	$(CC) -Wall -c -o fizzbuzz.o fizzbuzz.c
    
main.o: main.c fizzbuzz.h
	$(CC) -Wall -c -o main.o main.c
    
test_fizzbuzz.o: test_fizzbuzz.c fizzbuzz.h
	$(CC) -Wall -c -o test_fizzbuzz.o test_fizzbuzz.c
