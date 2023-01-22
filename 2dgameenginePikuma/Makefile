BUILDDIR=$(CURDIR)/build

### DECLARE SOME MAKEFILE VARIABLES ###
COMPILER = g++

LANGUAGE_STD = -std=c++17

COMPILER_FLAGS = -Werror -Wall

INCLUDE_PATH = -I"./libs/"

SRC_FILES = src/*.cpp \
						src/Game/*.cpp \
						src/Logger/*.cpp \
						src/ECS/*.cpp


LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -llua
OBJ_NAME = gameengine


build:
	# g++ -Werror -Wall -std=c++17 -I"./libs/" src/*.cpp src/Game/*.cpp src/Logger/*.cpp -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -llua  -o gameengine;

	$(COMPILER) $(COMPILER_FLAGS) $(LANGUAGE_STD) $(INCLUDE_PATH) $(SRC_FILES) $(LINKER_FLAGS) - $(OBJ_NAME)


run:
	# ./gameengine

	./$(OBJ_NAME)


clean:
	# rm gameengine

	rm $(OBJ_NAME)