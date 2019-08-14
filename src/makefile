test:
		cl /c LinkedList.cpp test.cpp
		lib LinkedList.obj
		link test.obj LinkedList.lib

testrun:
		cl /c LinkedList.cpp test.cpp
		lib LinkedList.obj
		link test.obj LinkedList.lib
		test.exe

linkedlistcl:
		cl /c LinkedList.cpp
		lib LinkedList.obj

testcl:
		cl /c test.cpp

clean:
		del *.obj
		del *.lib
		del *.exe