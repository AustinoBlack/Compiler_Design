CC = g++

CFlAGS =  -lfl -g

MeowText: language.l language.y node.h node.cpp opcodes.h opcodes.cpp helper.h helper.cpp symtab.h symtab.cpp
	bison -d language.y
	flex -l language.l
	$(CC) node.cpp language.tab.c lex.yy.c helper.cpp opcodes.cpp symtab.cpp $(CFLAGS) -o MeowText

.PHONY: clean test

clean:
	rm -f lex.yy.c language.tab.c MeowText

test:
	./MeowText < tests/test-clear-simple.meow > tests/clear-simple.out
