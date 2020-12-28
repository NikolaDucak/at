PROGRAM_NAME = at
COMPILER = g++
FLAGS = -I./inc/ -lpthread -lncurses -Wall -Wextra -Wpedantic
INSTAL_DIR = /usr/local/bin

all:
	$(COMPILER) $(FLAGS) src/*.cpp -o $(PROGRAM_NAME)

debug:
	$(COMPILER) $(FLAGS) src/*.cpp -o $(PROGRAM_NAME)_debug -g

install: all
	cp -f $(PROGRAM_NAME)  $(INSTAL_DIR)
	chmod 755 $(INSTAL_DIR)/$(PROGRAM_NAME)

uninstall:
	rm -f $(INSTAL_DIR)/$(PROGRAM_NAME)

