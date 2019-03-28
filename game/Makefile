CFLAGS = -Wall
OBJ = tui.o main.o view.o #control.o

all: game

game: $(OBJ)
	g++ $(CFLAGS) $(OBJ) -o game
clean:
	rm *.o
