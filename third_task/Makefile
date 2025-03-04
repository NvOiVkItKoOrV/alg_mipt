OBJ = obj/
BIN = bin/

FLAGS =  -Wall -Wextra -fsanitize=address

$(OBJ):
	@ mkdir -p $(OBJ)

$(BIN):
	@ mkdir -p $(BIN)

all: $(BIN)/my_program

$(BIN)/my_program: $(OBJ)/main.o | $(BIN)
	@ g++ $(FLAGS) $^ -o $@

$(OBJ)/main.o: main.c | $(OBJ)
	@ g++ -c $(FLAGS) $< -o $@

run: $(BIN)/my_program
	@ ./$(BIN)/my_program

clean:
	@ rm -rf $(OBJ) $(BIN)