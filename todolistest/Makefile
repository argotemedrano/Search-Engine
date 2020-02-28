# Let's declare some variables
CC       = g++
CPPFLAGS = -Wall -g
BIN_DIR  = bin
GTEST_LL = -I /usr/include/gtest/ -l gtest -l gtest_main -pthread

# IMPORTANT: $(GTEST_LL) needs to come *after* the source files

all: $(BIN_DIR)/todolist.o todolist-test-elab.cpp
	$(CC) $(CPPFLAGS) $(BIN_DIR)/todolist.o todolist-test-elab.cpp -o $(BIN_DIR)/bin-todolist-test-elab

$(BIN_DIR)/todolist.o: ../todolist.h ../todolist.cpp
	$(CC) $(CPPFLAGS) -c ../todolist.cpp -o $(BIN_DIR)/todolist.o

$(BIN_DIR)/todolistTest: test.cpp $(BIN_DIR)/todolist.o
	$(CC) $(CPPFLAGS) test.cpp -no-pie $(BIN_DIR)/todolist.o $(GTEST_LL) -o $(BIN_DIR)/todolistTest

.PHONY: tests clean

tests: $(BIN_DIR)/todolistTest
	-@valgrind --tool=memcheck --leak-check=full --track-origins=yes $(BIN_DIR)/todolistTest
	-@echo "--- All Tested!---"

clean:
	-@rm -rf $(BIN_DIR)/todolistTest
	-@echo "--- All Clean!---"