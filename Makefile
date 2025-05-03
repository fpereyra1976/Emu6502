BUILD_DIR = build
SRC_DIR = ./src
INCLUDE_DIR = ./include
TEST_DIR = tests

CXX = g++
CXXFLAGS = -I$(INCLUDE_DIR) -g -O0 -std=c++17 -march=native -mtune=native -fprofile-instr-generate -fcoverage-mapping

SRC = $(wildcard $(SRC_DIR)/*.cpp)
SRC := $(filter-out $(TEST_DIR)/%, $(SRC))
OBJ = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRC))

TEST_SRC = $(wildcard $(TEST_DIR)/*.cpp)
TEST_BIN = test_runner

PKG_CONFIG = $(shell which pkg-config)
ifeq ($(PKG_CONFIG),)
  GTEST_INC = -I/usr/local/include
  GTEST_LIB = -L/usr/local/lib -lgtest -lgtest_main
else
  GTEST_INC = $(shell pkg-config --cflags gtest)
  GTEST_LIB = $(shell pkg-config --libs gtest)
endif

TARGET = cpu

all: $(TARGET) $(TEST_BIN)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) main.cpp -o $(BUILD_DIR)/$@ $^

check: $(TEST_BIN)
	@echo "\033[1;36m[Ejecutando tests]\033[0m"
	./$(BUILD_DIR)/$(TEST_BIN)

$(TEST_BIN): $(TEST_SRC) $(OBJ)
	$(CXX) $(CXXFLAGS) $(GTEST_INC) $^ $(GTEST_LIB) -pthread -o $(BUILD_DIR)/$@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR) $(TARGET) $(TEST_BIN)
