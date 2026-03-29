BUILD_DIR = build
SRC_DIR = ./src
INCLUDE_DIR = ./include
TEST_DIR = tests

CXX = g++
CXXFLAGS = -I$(INCLUDE_DIR) -g -Wall -O0 -std=c++17 -fprofile-instr-generate -fcoverage-mapping

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

.PHONY: check-gtest
check-gtest:
	@if ! command -v pkg-config &> /dev/null; then \
		echo "📦 Instalando pkg-config y Google Test..."; \
		brew install pkg-config googletest || { echo "❌ Fallo en instalación"; exit 1; }; \
	elif ! pkg-config --exists gtest 2>/dev/null; then \
		echo "📦 Instalando Google Test..."; \
		brew install googletest || { echo "❌ Fallo en instalación"; exit 1; }; \
	fi
	@echo "✅ Google Test está disponible"

all: $(TARGET) $(TEST_BIN)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) main.cpp -o $(BUILD_DIR)/$@ $^

check: $(TEST_BIN)
	@echo "\033[1;36m[Ejecutando tests]\033[0m"
	./$(BUILD_DIR)/$(TEST_BIN)

$(TEST_BIN): check-gtest $(TEST_SRC) $(OBJ)
	$(CXX) $(CXXFLAGS) $(GTEST_INC) $(TEST_SRC) $(OBJ) $(GTEST_LIB) -pthread -o $(BUILD_DIR)/$@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR) $(TARGET) $(TEST_BIN)
