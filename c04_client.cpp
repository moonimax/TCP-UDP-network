#include "../common.h"
#include <string.h>


char* SERVERIP = (char*)"127.0.0.1" ;
#define SERVERPORT 9000
#define BUFSIZE    512

int main(int argc, char* argv[])
{
	int retval = -1 ;

//	get IP address from users
	if (argc > 1) 
		SERVERIP = argv[1] ;

//	initialize winsock
	WSADATA wsa;
	if (0 != WSAStartup(MAKEWORD(2, 2), &wsa))
		return 1 ;

//	create socket
	SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP) ;
	if (INVALID_SOCKET == sock)
		err_quit("socket()") ;

// connect()
	struct sockaddr_in serveraddr;
	memset(&serveraddr, 0, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	inet_pton(AF_INET, SERVERIP, &serveraddr.sin_addr);
	serveraddr.sin_port = htons(SERVERPORT);
	retval = connect(sock, (struct sockaddr*)&serveraddr, sizeof(serveraddr));
	if (SOCKET_ERROR == retval)
		err_quit("connect()");

//	variables declaration
	char buf[BUFSIZE + 1] = { 0, };
	int len = 0;

//	data communication
	while (1) 
	{
	//	get data to send
		printf("\n[data to send] ");
		if (fgets(buf, BUFSIZE + 1, stdin) == NULL)
			break;

	//	remove null terminate character
		len = (int)strlen(buf);
		if ('\n' == buf[len - 1])
			buf[len - 1] = '\0';

	//	no data to send
		if (0 == strlen(buf))
			break;

	//	send data
		retval = send(sock, buf, (int)strlen(buf), 0);
		if (SOCKET_ERROR == retval)
		{
			err_display("send()");
			break;
		}
		printf("[TCP client] %d bytes sent.\n", retval);

	//	receive data
		retval = recv(sock, buf, retval, MSG_WAITALL);
		if (SOCKET_ERROR == retval) 
		{
			err_display("recv()");
			break;
		}

	//	no data received
		else if (0 == retval)
			break;

	//	print the received data
		buf[retval] = '\0';
		printf("[TCP client] receive %d bytes.\n", retval);
		printf("[received data] %s\n", buf);

	//	closing condition
		retval = strncmp(buf, "99", sizeof(buf));
		if (0 == retval)
			break ;
	}

//	close socket
	closesocket(sock);

//	close socket
	WSACleanup();

	return 0;
}

