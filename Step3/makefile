
# cphex\makefile

LIBS=
all:	TCPEchoServer	TCPEchoClient	admin	LibSerHV.o 	LibSer.o	HandleTCPClient.o

admin:	data.h	admin.c	LibSerHV.o			
	echo "Compilation de admin"
	gcc -o admin	admin.c	LibSerHV.o 

TCPEchoServer:	TCPEchoServer.c	HandleTCPClient.o LibSer.o LibSerHV.o data.h Requete.h
	echo "Compilation de  TCPEchoServer"
	gcc -o	TCPEchoServer  TCPEchoServer.c  HandleTCPClient.o	LibSer.o LibSerHV.o
	
TCPEchoClient: TCPEchoClient.c Requete.h
	echo "Compilation de TCPEchoServer"
	gcc -o TCPEchoClient	TCPEchoClient.c	

LibSerHV.o:	LibSerHV.c	LibSerHV.h	data.h	
	echo "compilation de LibSerHV"
	gcc -c LibSerHV.c
	
LibSer.o:	LibSer.c	LibSer.h
	echo "Compilation de  LibSer.o"
	gcc -c LibSer.c

HandleTCPClient.o:	HandleTCPClient.c	HandleTCPClient.h
	echo "Compilation de HandleTCPClient.o"
	gcc -c HandleTCPClient.c
	
	

