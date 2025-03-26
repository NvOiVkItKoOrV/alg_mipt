OBJ = obj/
BIN = bin/


$(OBJ):
	@ mkdir -p $(OBJ)

$(BIN):
	@ mkdir -p $(BIN)

all: $(BIN)/my_program

$(BIN)/my_program: $(OBJ)/main.o | $(BIN)
	@ g++ $^ -o $@

$(OBJ)/main.o: main.cpp | $(OBJ)
	@ g++ -c $< -o $@

run: $(BIN)/my_program
	@ ./$(BIN)/my_program

clean:
	@ rm -rf $(OBJ) $(BIN)