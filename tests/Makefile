CC = g++
FLAGS = -std=c++11 -pedantic -O2 -Wall -Wextra -Werror -Wshadow -g -Wsign-conversion
DIR = "../"

all: md-parser md-parser-test

md-parser: ../pageparser.h ../md_parser.h ../md_parser.cpp
	$(CC) $(FLAGS) ../md_parser.h ../md_parser.cpp -c

md-parser-test: md_parser.o parsers/test-md.cpp
	$(CC) $(FLAGS) md_parser.o parsers/test-md.cpp ../util.cpp 	../webpage.cpp -o ./parsers/bin-test-md

tests: md-parser md-parser-test
	@valgrind --tool=memcheck --leak-check=yes ./parsers/bin-test-md ./parsers/md-simple1.in ./parsers/md-simple1-terms.out ./parsers/md-simple1-links.out
	@valgrind --tool=memcheck --leak-check=yes ./parsers/bin-test-md ./parsers/md-edge1.in ./parsers/md-edge1-terms.out ./parsers/md-edge1-links.out
	#@valgrind --tool=memcheck --leak-check=yes ./parsers/bin-test-md parsers/md-simple2.in parsers/md-simple2-terms.out parsers/md-simple2-links.out
	#@diff -s  parsers/md-simple1-terms-expected parsers/md-simple1-terms.out
	#@diff -s parsers/md-simple1-links-expected ./parsers/md-simple-links.out
	#@diff -s ./parsers/md-edge1-terms-expected ./parsers/md-edge2-terms.out
	#@diff -s ./parsers/md-edge1-links-expected ./parsers/md-edge2-links.out
	#@diff -s  parsers/md-simple2-terms-expected parsers/md-simple2-terms.out
	#@diff -s parsers/md-simple2-links-expected parsers/md-simple2-links.out
	
clean:
	rm -rf *o
	rm /parsers/bin-test-md