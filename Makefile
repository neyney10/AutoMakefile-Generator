mytest.cpp: Tree.o fake1.o
	g++ -std=c++1z Tree.o fake1.o mytest.cpp -o executable

Tree.o:
	g++ -std=c++1z -c Tree.cpp -o Tree.o

fake1.o:
	g++ -std=c++1z -c fake1.cpp -o fake1.o