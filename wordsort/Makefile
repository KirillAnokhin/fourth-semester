CC := gcc
CFLAGS := -g -Wall -MD
-include *.d

.PHONY: clean
	rm -rf *.o b	

$%.o: %.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) $< -o $@

BUILD_SRC := dict.c wf.c reader.c
BUILD_OBJ := $(BUILD_SRC:.c=.o)
.PHONY: build
build: dict
dict: $(BUILD_OBJ)
	$(CC) $(BUILD_OBJ) -o $@
