CC=g++

MeowText: language.l language.y node.h node.cpp
	bison -d language.y
	flex -l language.l
	$(CC) node.cpp language.tab.c lex.yy.c -lfl -g -o MeowText

.PHONY: clean

clean:
	rm -f lex.yy.c language.tab.c MeowText
