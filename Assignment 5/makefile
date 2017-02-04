all: Assn5

Assn5: Assn5.cpp TCPStream.o TCPConnector.o HTTPCnx.o
	g++ -o Assn5 Assn5.cpp \
		TCPStream.o TCPConnector.o HTTPCnx.o

TCPStream.o: TCPStream.cpp
	g++ -c -o TCPStream.o TCPStream.cpp

TCPConnector.o: TCPConnector.cpp
	g++ -c -o TCPConnector.o TCPConnector.cpp

HTTPCnx.o: HTTPCnx.cpp
	g++ -c -o HTTPCnx.o HTTPCnx.cpp

