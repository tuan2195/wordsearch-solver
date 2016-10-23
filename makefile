$(info Wordsearch by Tuan Dao | Usage: ./word filename sortAlgo useHash debugPrint)
all:
	g++ main.cpp grid.cpp wordlist.cpp -std=c++11 -Wall -Wno-deprecated -o word
