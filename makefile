CXX = g++
CXXFLAGS = -std=c++17 -Wall -Isrc

AnbarDar: main.o src/UTAnbar.o src/Bin.o src/Fruit.o
	$(CXX) $(CXXFLAGS) -o AnbarDar main.o src/UTAnbar.o src/Bin.o src/Fruit.o

main.o: main.cpp src/UTAnbar.hpp
	$(CXX) $(CXXFLAGS) -c main.cpp -o main.o

src/UTAnbar.o: src/UTAnbar.cpp src/UTAnbar.hpp src/Bin.hpp src/Fruit.hpp
	$(CXX) $(CXXFLAGS) -c src/UTAnbar.cpp -o src/UTAnbar.o

src/Bin.o: src/Bin.cpp src/Bin.hpp src/Fruit.hpp
	$(CXX) $(CXXFLAGS) -c src/Bin.cpp -o src/Bin.o

src/Fruit.o: src/Fruit.cpp src/Fruit.hpp
	$(CXX) $(CXXFLAGS) -c src/Fruit.cpp -o src/Fruit.o

clean:
	rm -f AnbarDar main.o src/*.o
