CC = g++
CFLAGS = -std=c++17 -O3 -g -Wall -Wextra -Wpedantic -Wstrict-aliasing
CFLAGS += -Wno-pointer-arith -Wno-newline-eof -Wno-unused-parameter -Wno-gnu-statement-expression
CFLAGS += -Wno-gnu-compound-literal-initializer -Wno-gnu-zero-variadic-macro-arguments
CFLAGS += -Iinclude
HEADER = $(wildcard include/*.hpp) $(wildcard include/**/*.hpp)
# CFLAGS += -Ilib/cglm/include -Ilib/glad/include -Ilib/glfw/include -Ilib/stb -Ilib/noise
# LDFLAGS = lib/glad/src/glad.o lib/cglm/.libs/libcglm.a lib/glfw/src/libglfw3.a lib/noise/libnoise.a . -lm

# GLFW required frameworks
# LDFLAGS += -framework OpenGL -framework IOKit -framework CoreVideo -framework Cocoa
LDFLAGS = -Llib/ -lglfw3 -lGL -lX11 -lXxf86vm -lXrandr -pthread -lXi -ldl

SRC  = $(wildcard src/**/*.cpp) $(wildcard src/*.cpp)
OBJ  = $(SRC:.cpp=.o)
BIN = bin

.PHONY: all clean

all: dirs game

dirs:
	mkdir -p ./$(BIN)

run: all
	$(BIN)/prog

game: $(OBJ)
	$(CC) -o $(BIN)/prog $^ $(LDFLAGS)

%.o: %.cpp $(HEADER)
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -rf $(BIN) $(OBJ)