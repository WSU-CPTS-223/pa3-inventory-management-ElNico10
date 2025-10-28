CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -g
TARGET = inventory_system
TEST_TARGET = TestContainers

SOURCES = main.cpp Product.cpp InventoryManager.cpp
TEST_SOURCES = TestContainers.cpp Product.cpp InventoryManager.cpp

HEADERS = Product.h Hashtable.h CategoryIndex.h InventoryManager.h

$(TARGET): $(SOURCES) $(HEADERS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCES)

$(TEST_TARGET): $(TEST_SOURCES) $(HEADERS)
	$(CXX) $(CXXFLAGS) -o $(TEST_TARGET) $(TEST_SOURCES)

test: $(TEST_TARGET)
	./$(TEST_TARGET)

clean:
	rm -f $(TARGET) $(TEST_TARGET)

all: $(TARGET) $(TEST_TARGET)

.PHONY: clean test all