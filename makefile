CC = g++

SRC_DIR = src
TEST_DIR = test
LIB_DIR = lib
OBJ_DIR = object
BIN_DIR = bin

GTEST_DIR = $(TEST_DIR)/gtest

INC_PATHS = -I$(INC_DIR) -I$(OBJ_DIR)

VPATH = $(INC_DIR) $(EXAMPLE_DIR) $(OBJ_DIR) $(LIB_DIR) $(SRC_DIR) $(TEST_DIR)

test: googletest
	$(CC) -I$(TEST_DIR) $(TEST_DIR)/*.cc -std=gnu++11 $(LIB_DIR)/libgtest.a -o $(BIN_DIR)/test.bin 
	./$(BIN_DIR)/test.bin

googletest:
	$(CC) -I$(TEST_DIR) -c $(GTEST_DIR)/gtest-all.cc -o $(OBJ_DIR)/gtest-all.o
	ar -rv $(LIB_DIR)/libgtest.a $(OBJ_DIR)/gtest-all.o

clean:
	rm -rf $(OBJ_DIR)/* $(LIB_DIR)/* $(BIN_DIR)/*