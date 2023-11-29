CC = g++

CFlAGS =  -lfl -g

MeowText: language.l language.y node.h node.cpp opcodes.h opcodes.cpp helper.h helper.cpp symtab.h symtab.cpp
	bison -d language.y
	flex -l language.l
	$(CC) node.cpp language.tab.c lex.yy.c helper.cpp opcodes.cpp symtab.cpp $(CFLAGS) -o MeowText

.PHONY: clean test

clean:
	rm -f lex.yy.c language.tab.c language.tab.h MeowText
	rm tests/all-maths.out
	rm tests/background-colors.out
	rm tests/ball.out
	rm tests/clear-simple.out
	rm tests/demo.out
	rm tests/loops-ifs.out
	rm tests/music-simple.out
	rm tests/pixel-colors.out
	rm tests/pixel-amount.out
	rm tests/pixel-simple.out
	rm tests/rectangle-colors.out
	rm tests/rectangle-multi.out
	rm tests/rectangle-simple.out

test:
	./MeowText < tests/test-clear-simple.meow > tests/clear-simple.out
	./MeowText < tests/test-pixel-colors.meow > tests/pixel-colors.out
	./MeowText < tests/test-pixel-simple.meow > tests/pixel-simple.out
	./MeowText < tests/test-rectangle-simple.meow > tests/rectangle-simple.out
	./MeowText < tests/test-background-colors.meow > tests/background-colors.out
	./MeowText < tests/test-rectangle-colors.meow > tests/rectangle-colors.out
	./MeowText < tests/test-rectangle-multi.meow > tests/rectangle-multi.out
	./MeowText < tests/test-loops-and-if.meow > tests/loops-ifs.out
	./MeowText < tests/test-all-maths.meow > tests/all-maths.out
	./MeowText < tests/test-pixel-amount.meow > tests/pixel-amount.out
	./MeowText < tests/ball-demo.meow > tests/ball.out
	./MeowText < tests/demo.meow > tests/demo.out
	./MeowText < tests/test-music-simple.meow > tests/music-simple.out
