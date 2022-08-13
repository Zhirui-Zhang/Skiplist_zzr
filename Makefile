main: test/main.cpp skiplist/node.h skiplist/skiplist.h
	g++ -o main test/main.cpp skiplist/node.h skiplist/skiplist.h

clean:
	rm -r skiplist
