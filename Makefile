CXX = g++
# Добавьте флаги для статической компиляции
CXXFLAGS = -std=c++17 -Wall -Wextra -static-libgcc -static-libstdc++
TARGET_MAIN = matrix_app
TARGET_TEST = test_app
SRC_DIR = src

all: $(TARGET_MAIN) $(TARGET_TEST)

$(TARGET_MAIN): $(SRC_DIR)/main.cpp $(SRC_DIR)/matrix.cpp $(SRC_DIR)/matrix.h
	$(CXX) $(CXXFLAGS) -o $(TARGET_MAIN) $(SRC_DIR)/matrix.cpp $(SRC_DIR)/main.cpp

$(TARGET_TEST): $(SRC_DIR)/test.cpp $(SRC_DIR)/matrix.cpp $(SRC_DIR)/matrix.h
	$(CXX) $(CXXFLAGS) -o $(TARGET_TEST) $(SRC_DIR)/matrix.cpp $(SRC_DIR)/test.cpp

test: $(TARGET_TEST)
	./$(TARGET_TEST)

docs:
	doxygen Doxyfile

clean:
	rm -f $(TARGET_MAIN) $(TARGET_TEST)

.PHONY: all test clean docs