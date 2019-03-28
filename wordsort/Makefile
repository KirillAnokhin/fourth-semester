CFLAGS=-Wall -g
OBJ=hash.o reader.o wf.o test.o gtest.o

all: dict
		
dict:	$(OBJ)
	gcc $(CFLAGS) $(OBJ) -o dict
clean:
	rm *.o

