Austin Black & Abby Cocker

to compile:
	flex language.l
	bison -d language.y
	g++ lex.yy.c language.tab.c node.cpp -lfl -o MeowText

to run:
	./Meowtext  
