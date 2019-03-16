executable: mytest.o Tree.o fake1.o
	g++ -std=c++1z mytest.o Tree.o fake1.o -o executable

mytest.o: mytest.cpp Tree.hpp fake1.hpp 
	g++ -std=c++1z -c mytest.cpp -o mytest.o

Tree.o: Tree.cpp Tree.hpp 
	g++ -std=c++1z -c Tree.cpp -o Tree.o

fake1.o: fake1.cpp fake1.hpp 
	g++ -std=c++1z -c fake1.cpp -o fake1.o

clean:
	rm -f *.o executable