# Auto "makefile" maker for c++ files
using the g++ compiler (for now, might be generic in later versions)

## Dependencies
Required java-10 or later.

## Ready jar file
at CPP_Tester -> AutoMakefile.jar

### How to use?
java -jar AutoMakefile.jar <mainfile.cpp>

### Example:
java -jar AutoMakefile.jar TreeTest.cpp

### Sample output:
D:\temp\Projects\Java\AutoMakefile\CPP_Tester>"C:\Program Files\Java\jdk-11.0.1\bin\java" -jar AutoMakefile.jar TreeTest.cpp
Starting AutoMaker Version: 1.1-Beta
Scanning file: D:\temp\Projects\Java\AutoMakefile\CPP_Tester\TreeTest.cpp
found dependency on line: 9, dependency: #include "badkan.hpp"
An error occured while scanning the file: badkan.cpp, for dependancies.
found dependency on line: 10, dependency: #include "Tree.hpp"
--- Here is the makefile preview: ---
executable: TreeTest.o Tree.o
        g++ -std=c++1z TreeTest.o Tree.o -o executable

TreeTest.o: TreeTest.cpp badkan.hpp Tree.hpp
        g++ -std=c++1z -c TreeTest.cpp -o TreeTest.o

Tree.o: Tree.cpp Tree.hpp
        g++ -std=c++1z -c Tree.cpp -o Tree.o

clean:
        rm -f *.o executable
--- Creating makefile: saved ---
