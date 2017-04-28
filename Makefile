all: web

web: main.cpp socket.cpp processpool.cpp cgi_conn.cpp HttpRequest.cpp HttpResponse.cpp HttpState.cpp
	g++ -Wall -g -std=c++11 $^ -o $@
	sudo chown root web
	sudo chmod u+s web

clean:
	sudo rm -rf web
