#include "../common.h"

#define REMOTEIP	"255.255.255.255"
#define REMOTEPORT	9000
#define BUFSIZE		512

int main(int argc, char* argv[])
{
	int retval = 0;

	//	initialize winsock
	WSADATA wsa;
	if (0 != WSAStartup(MAKEWORD(2, 2), &wsa))
		return 1;

	//	create socket
	SOCKET sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (INVALID_SOCKET == sock)
		err_quit("socket()");

	//	activate broadcast function
	DWORD bEnable = 1;
	retval = setsockopt(sock, SOL_SOCKET, SO_BROADCAST, (const char*)&bEnable, sizeof(bEnable));
	if (SOCKET_ERROR == retval)
		err_quit("setsockopt()");

	// connect()
	struct sockaddr_in remoteaddr;
	memset(&remoteaddr, 0, sizeof(remoteaddr));
	remoteaddr.sin_family = AF_INET;
	inet_pton(AF_INET, REMOTEIP, &remoteaddr.sin_addr);
	remoteaddr.sin_port = htons(REMOTEPORT);

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
		retval = sendto(sock, buf, (int)strlen(buf), 0, (struct sockaddr*)&remoteaddr, sizeof(remoteaddr));
		if (SOCKET_ERROR == retval)
		{
			err_display("sendto()");
			break;
		}
		printf("[UDP client] %d bytes have been sent.\n", retval);
	}

	//	close socket
	closesocket(sock);

	//	close socket
	WSACleanup();

	return 0;
}

