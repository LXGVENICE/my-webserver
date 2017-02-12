all: web

web : main.cpp HttpState.cpp
	g++ -Wall -std=c++11 $^ -o $@

clean:
	rm -rf web
