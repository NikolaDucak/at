PROGRAM_NAME = at
COMPILER = g++
FLAGS = -I./inc/ -lpthread -lncurses -Wall -Wextra -Wpedantic

all:
	$(COMPILER) $(FLAGS) src/*.cpp -o $(PROGRAM_NAME)

debug:
	$(COMPILER) $(FLAGS) src/*.cpp -o $(PROGRAM_NAME)_debug -g

install:
	cp $(PROGRAM_NAME)  /bin/
