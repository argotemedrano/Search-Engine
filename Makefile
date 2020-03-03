CC = g++
FLAGS = -std=c++11 -g -Wall -Werror -Wshadow -Wsign-conversion -pedantic -O2 -Wall 
OTHER = -Wextra 
all: search-shell

search-shell: pageparser.h searchui.cpp searcheng.cpp handler.h handler.cpp combiners.cpp cmdhandler.cpp webpage.cpp md_parser.cpp txt_parser.cpp util.cpp search-shell.cpp
	$(CC) $(FLAGS) searchui.cpp searcheng.cpp handler.cpp combiners.cpp cmdhandler.cpp webpage.cpp md_parser.cpp txt_parser.cpp util.cpp search-shell.cpp -o search-shell


clean:
	rm -rf *o