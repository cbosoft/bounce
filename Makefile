CXX ?= g++
CFLAGS = -Wall -Wextra -Werror -Wno-unused-parameter -std=c++17 -O2

# set the compiler flags
LINK = `sdl2-config --libs --cflags` -lSDL2_image -larmadillo -lm

# name of executable
EXE := bounce

GAME = obj/game/ctor.o\
			 obj/game/dtor.o\
			 obj/game/input.o\
			 obj/game/physics.o\
			 obj/game/render.o\
			 obj/game/run.o

SHAPES = obj/shapes/geometric_equation.o\
				 obj/shapes/circle.o\
				 obj/shapes/line.o

OBJECT = obj/object/object.o

OBJ = obj/main.o $(GAME) $(SHAPES) $(OBJECT)

## Colours
COL_OBJ = $(shell tput setaf 3 2>/dev/null)
COL_EXE = $(shell tput setaf 4 2>/dev/null)
COL_RST = $(shell tput sgr0 2>/dev/null)
COL_BLD = $(shell tput bold 2>/dev/null)

.SECONDARY:

obj/%.o: src/%.cpp $(HDR)
	@printf "$(COL_OBJ)ASSEMBLING OBJECT $@$(COL_RST)\n"
	@mkdir -p `dirname $@`
	@$(CXX) $(CFLAGS) $(DEFS) $< -c -o $@


.PHONY: all options

all: options $(EXE)

options:
	@printf "Compiler: $(COL_BLD)$(CXX)$(COL_RST)\n"

# recipe for building the final executable
$(EXE): $(OBJ) $(HDR) Makefile
	@printf "$(COL_OBJ)LINKING OBJECTS TO EXECUTABLE $@$(COL_RST)\n"
	@$(CXX) -o $@ $(OBJ) $(CFLAGS) $(LINK)

clean:
	rm -rf $(EXE) obj

.PHONY: all clean
