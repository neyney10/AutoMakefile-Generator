executable: TreeTest.o Tree.o
	g++ -std=c++1z TreeTest.o Tree.o -o executable

TreeTest.o: TreeTest.cpp badkan.hpp Tree.hpp 
	g++ -std=c++1z -c TreeTest.cpp -o TreeTest.o

Tree.o: Tree.cpp Tree.hpp 
	g++ -std=c++1z -c Tree.cpp -o Tree.o

clean:
	rm -f *.o executable