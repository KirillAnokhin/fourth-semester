CFLAGS = -Wall -g
OBJ = control.o game.o human.o main.o tui.o view.o
EXE = game

all: $(EXE)

game: $(OBJ)
	$(CXX) $(CFLAGS) $(OBJ) -o $(EXE)
clean:
	$(RM) $(OBJ) $(EXE)
