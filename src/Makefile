CC = g++

CFlAGS =  -lfl -g

MeowText: language.l language.y node.h node.cpp
	bison -d language.y
	flex -l language.l
	$(CC) node.cpp language.tab.c lex.yy.c $(CFLAGS) -o MeowText

.PHONY: clean test

clean:
	rm -f lex.yy.c language.tab.c MeowText

test:
	./MeowText < ../tests/test-simple.lang
