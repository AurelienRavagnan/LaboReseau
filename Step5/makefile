
# cphex\makefile

LIBS=
all:	TCPEchoServer	TCPEchoClient	admin	LibSerAR.o 	LibSer.o	HandleTCPClient.o

admin:	data.h	admin.c	LibSerAR.o			
	echo "Compilation de admin"
	gcc -o admin	admin.c	LibSerAR.o 

TCPEchoServer:	TCPEchoServer.c	HandleTCPClient.o LibSer.o LibSerAR.o data.h Requete.h
	echo "Compilation de  TCPEchoServer"
	gcc -o	TCPEchoServer  TCPEchoServer.c  HandleTCPClient.o	LibSer.o LibSerAR.o
	
TCPEchoClient: TCPEchoClient.c Requete.h
	echo "Compilation de TCPEchoServer"
	gcc -o TCPEchoClient	TCPEchoClient.c	

LibSerAR.o:	LibSerAR.c	LibSerAR.h	data.h	
	echo "compilation de LibSerAR"
	gcc -c LibSerAR.c
	
LibSer.o:	LibSer.c	LibSer.h
	echo "Compilation de  LibSer.o"
	gcc -c LibSer.c

HandleTCPClient.o:	HandleTCPClient.c	HandleTCPClient.h
	echo "Compilation de HandleTCPClient.o"
	gcc -c HandleTCPClient.c
	
	

