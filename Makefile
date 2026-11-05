CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra

TARGET = lab10

all: $(TARGET)

$(TARGET): main.cpp
	$(CXX) $(CXXFLAGS) -o $(TARGET) main.cpp

clean:
	rm -f $(TARGET)