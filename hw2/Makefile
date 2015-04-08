all:
	g++ demo.cpp
%: %.c
	gcc $< -o $@
%: %.cpp
	g++ $< -o $@
clean:
	ls . | grep -v 'BigData\|small.txt\|Makefile' | xargs rm -rf
