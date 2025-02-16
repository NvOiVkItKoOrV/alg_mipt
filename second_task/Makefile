SRC = src/
OBJ = obj/
BIN = bin/

FLAGS = -D _DEBUG -ggdb3 -std=c++17 -O0 -Wall -Wextra -Weffc++ -Waggressive-loop-optimizations \
        -Wc++14-compat -Wmissing-declarations -Wcast-align -Wcast-qual -Wchar-subscripts -Wconditionally-supported \
        -Wconversion -Wctor-dtor-privacy -Wempty-body -Wfloat-equal -Wformat-nonliteral -Wformat-security \
        -Wformat-signedness -Wformat=2 -Winline -Wlogical-op -Wopenmp-simd -Woverloaded-virtual -Wpacked \
        -Wpointer-arith -Winit-self -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel \
        -Wstrict-overflow=2 -Wsuggest-attribute=noreturn -Wsuggest-final-methods -Wsuggest-final-types -Wsuggest-override \
        -Wswitch-default -Wswitch-enum -Wsync-nand -Wundef -Wunreachable-code -Wunused -Wuseless-cast -Wvariadic-macros \
        -Wno-literal-suffix -Wno-missing-field-initializers -Wno-narrowing -Wno-old-style-cast -Wno-varargs -Wstack-protector \
        -fcheck-new -fsized-deallocation -fstack-protector -fstrict-overflow -flto-odr-type-merging -fno-omit-frame-pointer \
        -Wlarger-than=8192 -Wstack-usage=8192 -pie -fPIE -Werror=vla \
        -fsanitize=address,alignment,bool,bounds,enum,float-cast-overflow,float-divide-by-zero,integer-divide-by-zero,leak,nonnull-attribute,null,object-size,return,returns-nonnull-attribute,shift,signed-integer-overflow,undefined,unreachable,vla-bound,vptr

# Ensure the obj/ and bin/ directories exist
$(OBJ):
	@ mkdir -p $(OBJ)

$(BIN):
	@ mkdir -p $(BIN)

all: $(BIN)my_program

$(BIN)my_program: $(OBJ)main.o $(OBJ)input_func.o $(OBJ)queue_func.o | $(BIN)
	@ g++ $(FLAGS) $^ -o $@

$(OBJ)main.o: $(SRC)main.c | $(OBJ)
	@ g++ -c -I./include $(FLAGS) $< -o $(OBJ)main.o

$(OBJ)input_func.o: $(SRC)input_func.c | $(OBJ)
	@ g++ -c -I./include $(FLAGS) $< -o $(OBJ)input_func.o

$(OBJ)queue_func.o: $(SRC)queue_func.c | $(OBJ)
	@ g++ -c -I./include $(FLAGS) $< -o $(OBJ)queue_func.o

run: $(BIN)my_program	
	@ ./$(BIN)my_program 

clean:
	@ rm -rf $(OBJ) $(BIN)

