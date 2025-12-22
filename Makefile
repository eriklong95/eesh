SRC := ./src
BUILD := ./build
OBJ := $(BUILD)/obj

SRCS := $(wildcard $(SRC)/*.c)
OBJS := $($(SRCS):$(SRC)/%.c=$(OBJ)/%.o)

eesh: $(OBJS)
	$(CC) -o $@ $^

$(OBJ)/%.o: $(SRC)/%.c $(OBJ)
	$(CC) -c -o $@ $<

$(OBJ): $(BUILD)
	mkdir -p $(OBJ)

$(BUILD):
	mkdir -p $(BUILD)

.PHONY: clean
clean:
	rm -r $(BUILD)

