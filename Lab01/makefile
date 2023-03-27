CXX = g++
CXXFLAGS = -std=c++11 -g -fopenmp -O3
LFlAGS = -L/usr/lib/x86_64-linux-gnu/mkl -lblas -l./
EXE = main.exe
OBJ = FM.o utils.o main.o
SRC_DIR = ./src
HPP = $(SRC_DIR)/FM.hpp $(SRC_DIR)/utils.hpp
CPP = $(SRC_DIR)/FM.cpp $(SRC_DIR)/utils.cpp

all: $(EXE)
	@echo Compile successfully

$(EXE): $(OBJ)
	$(CXX) -o $@ $^ $(LFLAGS)

$(OBJ): $(HPP) $(CPP) main.cpp
	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/FM.cpp
	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/utils.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp

clean:
	rm -rf *.o