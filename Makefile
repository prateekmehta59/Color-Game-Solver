

CXX=g++
CXX_FLAGS=-g -std=c++11

PROJ_INC=include

GAME_INC=game
BOARD_SRC=game/board.cc
BOARD_OBJ=board.o

TEST_BASIC_SRC=test/basic.cc

TEST_BIN=run_test

default: all

all: board test_basic

board: $(BOARD_SRC)
	$(CXX) -c $(CXX_FLAGS) -I$(PROJ_INC) -I$(GAME_INC) $(BOARD_SRC) -o $(BOARD_OBJ)

test_basic: board 
	$(CXX) $(CXX_FLAGS) -I$(PROJ_INC) -I$(GAME_INC) -o $(TEST_BIN) \
	$(TEST_BASIC_SRC) $(BOARD_OBJ)
	./$(TEST_BIN)

clean:
	rm *.o
	rm $(TEST_BIN)

.PHONY: clean

