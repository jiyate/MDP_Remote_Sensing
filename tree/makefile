CXX = g++
cc = gcc
 
LIB = -lpthread -ldl
BIN = sqlite tree
 
all : $(BIN)
sqlite : sqlite3.c shell.c
	$(cc) -o $@ $^ $(LIB) 
tree : tree.cpp sqlite3.o
	$(CXX) -o $@ $^ $(LIB) 
sqlite3.o : sqlite3.c
	$(cc) -o $@ -c $^

clean :
	rm -f $(BIN)

.PHONY: all, clean