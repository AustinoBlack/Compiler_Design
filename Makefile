Scanner: obj/scanner.o obj/print_token.o main.cpp
	g++ -g -Wno-write-strings main.cpp obj/scanner.o obj/print_token.o -o Scanner

obj/scanner.o: scanner.h scanner.cpp
	g++ -g -c scanner.cpp -o obj/scanner.o

obj/print_token.o: scanner.h print_token.cpp
	g++ -g -c print_token.cpp -o obj/print_token.o

.PHONY: clean

clean: 
	rm -f obj/*.o Scanner
