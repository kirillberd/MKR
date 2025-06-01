CXX = g++
CXXFLAGS = -Wall -std=c++17 -Isrc/headers
SOURCES = src/main.cc src/Node.cc src/InitPlate.cc src/writePlateTemp.cc src/PlateSolver.cc
TARGET = thermal_sim.o

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(TARGET)

clean:
	rm -f $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: clean run