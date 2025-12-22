CC = gcc

SRC := ./src
BUILD := ./build
OBJ := $(BUILD)/obj
TESTS := ./tests
BUILD_TEST := $(BUILD)/tests

$(BUILD)/eesh: $(OBJ)/csapp.o $(OBJ)/lib.o $(OBJ)/main.o
	$(CC) -o $@ $^

$(OBJ)/%.o: $(SRC)/%.c $(OBJ)
	$(CC) -c -o $@ $<

$(OBJ): $(BUILD)
	mkdir -p $(OBJ)

$(BUILD):
	mkdir -p $(BUILD)

$(BUILD_TEST)/%: $(TESTS)/%.c $(OBJ)/csapp.o $(OBJ)/lib.o $(BUILD_TEST)
	$(CC) -o $@ $(OBJ)/csapp.o $(OBJ)/lib.o $<

$(BUILD_TEST):
	mkdir -p $(BUILD_TEST)

.PHONY: clean
clean:
	rm -r $(BUILD)

.PHONY: run
run: $(BUILD)/eesh
	$<

