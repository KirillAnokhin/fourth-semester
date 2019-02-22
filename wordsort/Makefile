OBJ = dict.o reader.o
PROG = dict
CFLAGS += -Wall -g
HDR = dict.h reader.h

all : $(PROG)
$(PROG):$(OBJ)
	$(cc) -o $@ $(PROG) $(OBJ) $(CFLAGS)

$(OBJ):$(HDR)

clean: 
	$(RM) $(OBJ) 
